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
#from ROOT import TChain

MJPSI = 3.097  # GeV
ECMS = 3.09  # GeV

mgamgam = ROOT.vector('double')()

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
            mgamgam.push_back(mass_gam12)
    #		cut_pi=(mass_gam12 < 0.125 or mass_gam12 > 0.145)
    #		if cut_pi:
    #		    continue    
def main():
    args = sys.argv[1:]

    if (len(args) < 2):
        print ('input error')
    infile = args[0]
    outfile = args[1]
    check_outfile_path(outfile)

    chain = ROOT.TChain("xi0", "")
    # chain.Add("dat/run/jpsi_inclusive/rootfile_data09/jpsi_data09-*.root")
    chain.Add(infile)
    fout = ROOT.TFile(outfile, "RECREATE")
    entries = chain.GetEntries()

    t_out = ROOT.TTree('tree', 'tree')
    t_out.Branch('mgamgam', mgamgam)
    
    n_run = array('i', [0])
    n_event = array('i', [0])
    t_out.Branch("run", n_run, "run/I")
    t_out.Branch("event", n_event, "event/I")
    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()
    print ('entries='), entries
    for k in range(entries):
        pbar.update(k+1)
        chain.GetEntry(k)
        n_run[0] = chain.run
        n_event[0] = chain.event
        mass_loop_pi0(chain)
        
        t_out.Fill()
        mgamgam.clear()
       
    t_out.Write()
    t_out.Print()
    fout.Close()
    pbar.finish()
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur)

if __name__ == '__main__':
    main()
