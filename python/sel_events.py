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
ECMS = 3.09  # GeV

n_run = array('i', [0])
n_event = array('i', [0])
n_indexmc = array('i',[0])
n_pdgid = array('i', 100*[-99])
n_motheridx = array('i', 100*[-99])
#ngamgam = array('i', [0])
mgamgam = array('d',[0])
t_out = ROOT.TTree('pi0', 'pi0')
t_out.Branch("run", n_run, "run/I")
t_out.Branch("event", n_event, "event/I")
t_out.Branch("indexmc", n_indexmc, "indexmc/I")
t_out.Branch("pdgid", n_pdgid, "pdgid[100]/I")
t_out.Branch("motheridx", n_motheridx, "motheridx[100]/I")
#t_out.Branch('ngamgam', ngamgam,"ngamgam/I")
t_out.Branch('mgamgam', mgamgam,"mgamgam/D")

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
#        print chain.run, chain.event
#        print chain.p4shw[tempindexgshw1],chain.p4shw[tempindexgshw1+1],chain.p4shw[tempindexgshw1+2],chain.p4shw[tempindexgshw1+3]
#        print chain.p4shw[tempindexgshw2],chain.p4shw[tempindexgshw2+1],chain.p4shw[tempindexgshw2+2],chain.p4shw[tempindexgshw2+3]
#        print p4shw_gam12.M()
    else:
        mgamgam[0]=-666
    t_out.Fill()

# loop through each gamma photons to reconstruct pi0 candidates
def mass_loop_pi0(chain):
    #print('\n')
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
            mgamgam[ngamgam[0]]=mass_gam12
            #print mgamgam[ngamgam[0]]
            
        #     cut_pi=(mass_gam12 < 0.125 or mass_gam12 > 0.145)
        # if cut_pi:
        #     continue
            t_out.Fill()
	ngamgam[0]+=1
    #exit()
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
	for ii in range(n_indexmc[0]):
	    n_pdgid[ii]=chain.p4truth[ii*6+4]
	    n_motheridx[ii]=chain.p4truth[ii*6+5]
        
#	mass_loop_pi0(chain)
#       ngamgam[0]=0
	mass_diff_pi0(chain)
          
    t_out.Write()
    t_out.Print()
    fout.Close()
    pbar.finish()
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur)

if __name__ == '__main__':
    main()
