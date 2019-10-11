#!/usr/bin/env python

"""
Event Selection
"""
__author__="AMIT PATHAK <amit@ihep.ac.cn>"
__copyright__="Copyright (c) AMIT PATHAK"
__created__="[2019-09-13]"

import sys,os,math
import ROOT
#from ROOT import TChain
from progressbar import Bar, Percentage, ProgressBar
from time import time
from tools import duration, check_outfile_path
from array import array

MJPSI = 3.097 #GeV
ECMS = 3.09 #GeV

#global histogram
h_run = ROOT.TH1D('h_run','run',100, 0, 25330)
h_event = ROOT.TH1D('h_event', 'event', 100,0 ,10000000)
h_ncharged = ROOT.TH1D('h_ncharged', 'ncharged', 100, 1, 10)
h_ngoodcharged = ROOT.TH1D('h_ngoodcharged', 'ngcharged',100, 0, 10)
h_nshower = ROOT.TH1D('h_nshower', 'nshw', 100, 1, 10)
h_ngoodshower = ROOT.TH1D('h_ngoodshower', 'ngshw',100, 0, 10)
h_ne = ROOT.TH1D('h_ne', 'ne', 100, -1, 3)
h_energy_gamma1 = ROOT.TH1D('h_energy_gamma1', 'energy_gamma1', 100, 0, 2)
h_energy_gamma2 = ROOT.TH1D('h_energy_gamma2', 'energy_gamma2', 100, 0, 2)
h_pi0 = ROOT.TH1D ('h_pi0','mass_gam12',100, 0, 1)
h_lambda = ROOT.TH1D ('h_lambda','mass_lambda',100, 1, 1.3)
h_xi0 = ROOT.TH1D ('h_xi0','mass_xi0',100, 1, 3)
h_rec_mass_xi0 = ROOT.TH1D ('h_rec_mass_xi0','rec_mass_xi0',100, 0, 2)

def main ():     
    args = sys.argv[1:]

    if (len(args) < 2):
        print 'input error'
    infile = args[0]
    outfile = args[1]
    check_outfile_path(outfile)
   
    chain = ROOT.TChain("xi0","")
    # chain.Add("dat/run/jpsi_inclusive/rootfile_data09/jpsi_data09-*.root")
    chain.Add(infile)
    fout = ROOT.TFile(outfile, "RECREATE")
    entries = chain.GetEntries()
    
    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()
    cms_p4 = ROOT.TLorentzVector(0.011*ECMS, 0, 0, ECMS)
    print 'entries=', entries

    cms_p4 = ROOT.TLorentzVector(0.011*ECMS, 0, 0, ECMS)

    for k in range(entries):
        pbar.update(k+1)
        chain.GetEntry(k)
        h_run.Fill(chain.run)
        h_event.Fill(chain.event)
        h_ncharged.Fill(chain.ncharged)
        h_ngoodcharged.Fill(chain.ngcharged)
        h_nshower.Fill(chain.nshw)
        h_ngoodshower.Fill(chain.ngshw)
        h_ne.Fill(chain.ne)
        
        # setting gammas with p4shower information
        p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[0],chain.p4shw[1],chain.p4shw[2],chain.p4shw[3])
        p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[6],chain.p4shw[7],chain.p4shw[8],chain.p4shw[9])
        p4shw_gam12 = p4shw_gam1 + p4shw_gam2
        mass_gam12 = p4shw_gam12.M()
        h_pi0.Fill(mass_gam12)

        energy_gamma1 = p4shw_gam1.E()
        energy_gamma2 = p4shw_gam2.E()
        h_energy_gamma1.Fill(energy_gamma1)
        h_energy_gamma2.Fill(energy_gamma2)

        p4_lambda =ROOT.TLorentzVector(chain.p4lambda[0],chain.p4lambda[1],chain.p4lambda[2],chain.p4lambda[3])
        mass_lambda = p4_lambda.M()
        h_lambda.Fill(mass_lambda)

        p4_xi0 = p4shw_gam12 + p4_lambda
        mass_xi0 = p4_xi0.M()
        h_xi0.Fill(mass_xi0)

        p4_rec_xi0 = cms_p4 - p4_xi0
        rec_mass_xi0 = p4_rec_xi0.M()
        h_rec_mass_xi0.Fill(rec_mass_xi0)

    h_run.Write()
    h_event.Write()
    h_ncharged.Write()
    h_ngoodcharged.Write()
    h_nshower.Write()
    h_ngoodshower.Write()
    h_ne.Write()
    h_energy_gamma1.Write()
    h_energy_gamma2.Write()
    h_pi0.Write()
    h_lambda.Write()
    h_xi0.Write()
    h_rec_mass_xi0.Write()

    fout.Close()
    pbar.finish()
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur)
if __name__ =='__main__':
    main()
