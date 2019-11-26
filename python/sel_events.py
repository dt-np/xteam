#!/usr/bin/env python

"""
Event Selection
"""
__author__ = "AMIT PATHAK <amit@ihep.ac.cn>"
__copyright__ = "Copyright (c) AMIT PATHAK"
__created__ = "[2019-09-13]"

from array import array
from tools import duration, check_outfile_path
from time import time
from progressbar import Bar, Percentage, ProgressBar
import ROOT
import sys
import os
import math

MJPSI = 3.097  # GeV
ECMS = 3.0969  # GeV

n_run = array('i', [0])
n_event = array('i', [0])
n_indexmc = array('i',[0])
n_pdgid = array('i', 100*[-99])
n_motheridx = array('i', 100*[-99])
mgamgam = array('d',[0])
mlambda = array('d',[0])
mxi0 = array('d',[0])
mrecxi0 = array('d',[0])
nextragam = array('i', [0])
eextragam = array('d', 100*[-99])
t_out = ROOT.TTree('pi0', 'pi0')
t_out.Branch("run", n_run, "run/I")
t_out.Branch("event", n_event, "event/I")
t_out.Branch("indexmc", n_indexmc, "indexmc/I")
t_out.Branch("pdgid", n_pdgid, "pdgid[100]/I")
t_out.Branch("motheridx", n_motheridx, "motheridx[100]/I")
t_out.Branch('mgamgam', mgamgam,"mgamgam/D")
t_out.Branch('mlambda', mlambda, "mlambda/D")
t_out.Branch('mxi0', mxi0, "mxi0/D")
t_out.Branch('mrecxi0', mrecxi0, "mrecxi0/D")
t_out.Branch('nextragam', nextragam, "nextragam/I")
t_out.Branch('eextragam', eextragam, "eextragam[100]/D")

cms_p4 = ROOT.TLorentzVector(0.011*ECMS, 0, 0, ECMS)

# select the pi0 candidate by comparing the closest mass from pdg value
def mass_diff_pi0(chain):
    tempindexgshw1=-1
    tempindexgshw2=-1
    tempminmassdifference=999.
    for l in range(chain.ngshw):
        for m in range(chain.ngshw):
            if l>=m:
                continue
            indexgshw1 = l*6
            indexgshw2 = m*6

            p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[indexgshw1],chain.p4shw[indexgshw1+1],chain.p4shw[indexgshw1+2],chain.p4shw[indexgshw1+3])
            p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[indexgshw2],chain.p4shw[indexgshw2+1],chain.p4shw[indexgshw2+2],chain.p4shw[indexgshw2+3])
            p4shw_gam12 = p4shw_gam1 + p4shw_gam2
            
            if tempminmassdifference>abs(p4shw_gam12.M()-0.1349766):
                tempindexgshw1=l*6
                tempindexgshw2=m*6
                tempminmassdifference=abs(p4shw_gam12.M()-0.1349766)
    if tempindexgshw2!=-1 and tempindexgshw1!=-1:
        p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[tempindexgshw1],chain.p4shw[tempindexgshw1+1],chain.p4shw[tempindexgshw1+2],chain.p4shw[tempindexgshw1+3])
        p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[tempindexgshw2],chain.p4shw[tempindexgshw2+1],chain.p4shw[tempindexgshw2+2],chain.p4shw[tempindexgshw2+3])
        p4shw_gam12 = p4shw_gam1 + p4shw_gam2
        mgamgam[0]=p4shw_gam12.M()
    else:
        mgamgam[0]=-666
    t_out.Fill()

# loop through each gamma photons to reconstruct pi0 candidates
def mass_loop_pi0(chain):
    #print('\n')
    p4_lambda = ROOT.TLorentzVector(chain.p4lambda[0], chain.p4lambda[1], chain.p4lambda[2], chain.p4lambda[3])
    mass_lambda = p4_lambda.M()
    mlambda[0] = mass_lambda
    for l in range(chain.ngshw):
        for m in range(chain.ngshw):
            if l >= m:
                continue
            #print('l= ',l, ' m= ',m)
            indexgshw1 = l*6
            indexgshw2 = m*6            
            p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[indexgshw1], chain.p4shw[indexgshw1+1], chain.p4shw[indexgshw1+2], chain.p4shw[indexgshw1+3])
            p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[indexgshw2], chain.p4shw[indexgshw2+1], chain.p4shw[indexgshw2+2], chain.p4shw[indexgshw2+3])
            p4shw_gam12 = p4shw_gam1 + p4shw_gam2
            mass_gam12 = p4shw_gam12.M()
            mgamgam[0]=mass_gam12

            p4_xi0 = p4shw_gam12 + p4_lambda
            mass_xi0 = p4_xi0.M()
            mxi0[0] = mass_xi0
            p4_rec_xi0 = cms_p4 - p4_xi0
            rec_mass_xi0 = p4_rec_xi0.M()
            mrecxi0[0] = rec_mass_xi0

            #filling the tree at candidate level 
            t_out.Fill()

def main():
    args = sys.argv[1:]

    if (len(args) < 2):
        print ('input error')
    infile = args[0]
    outfile = args[1]
    check_outfile_path(outfile)
    chain = ROOT.TChain("xi0", "")
    chain.Add(infile)
    fout = ROOT.TFile(outfile, "RECREATE")
    entries = chain.GetEntries()  
    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()
    print ('entries='), entries
    for k in range(entries):
        pbar.update(k+1)
        chain.GetEntry(k)
        n_run[0] = chain.run
        n_event[0] = chain.event
        n_indexmc[0] = chain.indexmc
        p4_lambda = ROOT.TLorentzVector(chain.p4lambda[0], chain.p4lambda[1], chain.p4lambda[2], chain.p4lambda[3])
        mass_lambda = p4_lambda.M()
        mlambda[0] = mass_lambda
        # if (mlambda[0] < 1.11 or mlambda[0] > 1.12):        
        #     continue
        for ii in range(n_indexmc[0]):
            n_pdgid[ii]=int(chain.p4truth[ii*6+4])
            n_motheridx[ii]=int(chain.p4truth[ii*6+5])
        Idgam1=-9
        Idgam2=-9
        idextra=0
        for ii in range(chain.ngshw):
            if chain.p4shw[ii*6+4]==chain.Idshw1:
                Idgam1=ii
            if chain.p4shw[ii*6+4]==chain.Idshw2:
                Idgam2=ii
            if Idgam1==-9 or Idgam2==-9:
            # print "there are not more than two gamma..."
                continue
            if chain.p4shw[ii*6+4] != chain.Idshw1 and chain.p4shw[ii*6+4] != chain.Idshw2:
                eextragam[idextra] = chain.p4shw[ii*6+3]
                idextra+=1
        nextragam[0]=idextra-1

        # Idgam1= chain.VIdG1[chain.Idshw1]
        # Idgam2=chain.VIdG2[chain.Idshw2]
        p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[Idgam1*6],chain.p4shw[Idgam1*6+1],chain.p4shw[Idgam1*6+2],chain.p4shw[Idgam1*6+3])
        p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[Idgam2*6],chain.p4shw[Idgam2*6+1],chain.p4shw[Idgam2*6+2],chain.p4shw[Idgam2*6+3])
        p4shw_gam12 = p4shw_gam1 + p4shw_gam2
        mass_gam12 = p4shw_gam12.M()
        mgamgam[0]=mass_gam12        
        p4_xi0 = p4shw_gam12 + p4_lambda
        mass_xi0 = p4_xi0.M()
        mxi0[0] = mass_xi0
        p4_rec_xi0 = cms_p4 - p4_xi0
        rec_mass_xi0 = p4_rec_xi0.M()
        mrecxi0[0] = rec_mass_xi0
        # mass_loop_pi0(chain)
        # mass_diff_pi0(chain)
        
        t_out.Fill()
    t_out.Write()
    t_out.Print()
    fout.Close()
    pbar.finish()
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur)

if __name__ == '__main__':
    main()
