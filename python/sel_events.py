#!/usr/bin/env python

"""
Event Selection
"""
__author__="AMIT PATHAK <amit@ihep.ac.cn>"
__copyright__="Copyright (c) AMIT PATHAK"
__created__="[2019-09-13]"

import sys
import os
import math
import ROOT
from progressbar import Bar, Percentage, ProgressBar
from time import time
from tools import duration, check_outfile_path
from array import array

MJPSI = 3.097 #GeV
ECMS = 3.09

#global histogram
h_run = ROOT.TH1D('h_run','run',100, -27120, -25330)
h_event = ROOT.TH1D('h_event', 'event', 100, 0, 20 )

def main ():     
    args = sys.argv[1:]

    if (len(args) < 2):
        print 'input error'
        
    infile = args[0]
    outfile = args[1]
    check_outfile_path(outfile)

    fin = ROOT.TFile(infile)
    t = fin.Get('xi0')
    
    fout = ROOT.TFile(outfile, "RECREATE")
    t_out = ROOT.TTree("xi0","xi0")
    
    print("I'm here at position 1")
    
    entries = t.GetEntries()
    print("I'm here at position 2")
    exit()
    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()
    #cms_p4 = ROOT.TLorentzVector(0.011*ECMS, 0, 0, ECMS)
    print 'entries=', entries
    for k in range(entries):
        pbar.update(k+1)
        t.GetEntry(k)
        h_run.Fill(t.run)
        h_event.Fill(t.event)
   
    h_run.Write()
    h_event.Write()
    t_out.Fill()
    t_out.Print()
    t_out.Write()

    fout.Close()
    pbar.finish()
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur)
if __name__ =='__main__':
    main()
