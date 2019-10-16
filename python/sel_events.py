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
# h_run = ROOT.TH1D('h_run','run',100, 0, 25330)
# h_event = ROOT.TH1D('h_event', 'event', 100,0 ,10000000)
# h_ncharged = ROOT.TH1D('h_ncharged', 'ncharged', 100, 1, 10)
# h_ngoodcharged = ROOT.TH1D('h_ngoodcharged', 'ngcharged',100, 0, 10)
# h_nshower = ROOT.TH1D('h_nshower', 'nshw', 100, 1, 10)
# h_ngoodshower = ROOT.TH1D('h_ngoodshower', 'ngshw',100, 0, 10)
# h_ne = ROOT.TH1D('h_ne', 'ne', 100, -1, 3)
# h_energy_gamma1 = ROOT.TH1D('h_energy_gamma1', 'energy_gamma1', 100, 0, 2)
# h_energy_gamma2 = ROOT.TH1D('h_energy_gamma2', 'energy_gamma2', 100, 0, 2)
# h_pi0 = ROOT.TH1D ('h_pi0','mass_gam12',100, 0, 0.5)
# h_lambda = ROOT.TH1D ('h_lambda','mass_lambda',100, 1, 1.3)
# h_xi0 = ROOT.TH1D ('h_xi0','mass_xi0',2000, 1, 3)
# h_rec_mass_xi0 = ROOT.TH1D ('h_rec_mass_xi0','rec_mass_xi0',100, 0, 2)

mgamgam = ROOT.vector('double')()
p4gam = ROOT.vector('double')()
mxi0 = ROOT.vector('double')()
mrecxi0 = ROOT.vector('double')()
mlambda = ROOT.vector('double')()
indexmc = ROOT.vector('double')()
p4truth = ROOT.vector('double')()
p4truthgam = ROOT.vector('double')()
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

   
    t_out = ROOT.TTree('tree', 'tree')
    t_out.Branch('mgamgam', mgamgam)
    t_out.Branch('p4gam',p4gam)
    t_out.Branch('mxi0', mxi0)
    t_out.Branch('mrecxi0', mrecxi0)
    t_out.Branch('mlambda', mlambda)
    t_out.Branch('indexmc', indexmc)
    t_out.Branch('p4truth', p4truth)
    t_out.Branch('p4truthgam', p4truthgam)

    n_run = array('i',[0])
    n_event = array('i',[0])
    t_out.Branch("run", n_run, "run/I")
    t_out.Branch("event", n_event, "event/I")

    
    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()
    cms_p4 = ROOT.TLorentzVector(0.011*ECMS, 0, 0, ECMS)
    print 'entries=', entries

    cms_p4 = ROOT.TLorentzVector(0.011*ECMS, 0, 0, ECMS)

    for k in range(entries):
#    for k in range(1):
        pbar.update(k+1)
        chain.GetEntry(k)         
        
	p4_lambda =ROOT.TLorentzVector(chain.p4lambda[0],chain.p4lambda[1],chain.p4lambda[2],chain.p4lambda[3])
        mass_lambda = p4_lambda.M()
        n_run[0] = chain.run
        n_event[0] = chain.event
        # setting gammas with p4shower information
        #the most energetic photon selection by comparing the energy of photons
        tempindexgam1=0
        tempindexgam2=0
        tempegam1=0.
        tempegam2=0.
        for l in range(chain.ngshw):
            indexgshw1 = l*6
            p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[indexgshw1],chain.p4shw[indexgshw1+1],chain.p4shw[indexgshw1+2],chain.p4shw[indexgshw1+3])
            if tempegam1<chain.p4shw[indexgshw1+3]:
                tempegam2=tempegam1
                tempindexgam2=tempindexgam1
                tempegam1=chain.p4shw[indexgshw1+3]
                tempindexgam1=l*6
                continue
            if tempegam2<chain.p4shw[indexgshw1+3]:
                tempegam2=chain.p4shw[indexgshw1+3]
                tempindexgam2=l*6
       
#	print tempindexgam1,tempindexgam2 
#        print tempegam1,tempegam2
#        print chain.p4shw[tempindexgam1],chain.p4shw[tempindexgam1+1],chain.p4shw[tempindexgam1+2],chain.p4shw[tempindexgam1+3]
#        print chain.p4shw[tempindexgam2],chain.p4shw[tempindexgam2+1],chain.p4shw[tempindexgam2+2],chain.p4shw[tempindexgam2+3]


#        tempindexgam1=0
#        tempindexgam2=0
#   	tempminmassdifference=999.
#    	for l in range(chain.ngshw):
#	    for m in range(chain.ngshw):
#		if l==m:
#			continue
#		indexgshw1 = l*6
#            	indexgshw2 = m*6
#            	p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[indexgshw1],chain.p4shw[indexgshw1+1],chain.p4shw[indexgshw1+2],chain.p4shw[indexgshw1+3])
#           	p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[indexgshw2],chain.p4shw[indexgshw2+1],chain.p4shw[indexgshw2+2],chain.p4shw[indexgshw2+3])
#           	p4shw_gam12 = p4shw_gam1 + p4shw_gam2
#          	p4_xi0 = p4shw_gam12 + p4_lambda
#		
#		if tempminmassdifference>abs(p4_xi0.M()-1.31486):
#                    tempindexgam1=l*6
#                    tempindexgam2=m*6
#                    tempminmassdifference=abs(p4_xi0.M()-1.31486)
                
	p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[tempindexgam1],chain.p4shw[tempindexgam1+1],chain.p4shw[tempindexgam1+2],chain.p4shw[tempindexgam1+3])
        p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[tempindexgam2],chain.p4shw[tempindexgam2+1],chain.p4shw[tempindexgam2+2],chain.p4shw[tempindexgam2+3])
        p4shw_gam12 = p4shw_gam1 + p4shw_gam2
    
        mass_gam12 = p4shw_gam12.M()

        
 	p4_xi0 = p4shw_gam12 + p4_lambda
 	mass_xi0 = p4_xi0.M()
 
 	p4_rec_xi0 = cms_p4 - p4_xi0
 	rec_mass_xi0 = p4_rec_xi0.M()
 
	mgamgam.push_back(mass_gam12)
   	
        for i in range(4):
	    p4gam.push_back(chain.p4shw[tempindexgam1+i])
	for i in range(4):
	    p4gam.push_back(chain.p4shw[tempindexgam2+i])
     
	mxi0.push_back(mass_xi0)
	mrecxi0.push_back(rec_mass_xi0)
	mlambda.push_back(mass_lambda)
	indexmc.push_back(chain.indexmc)
	for i in range(chain.indexmc*6):
	    p4truth.push_back(chain.p4truth[i])
	    if i%6==4 and chain.p4truth[i]==22:
		for j in range(4):
    		    p4truthgam.push_back(chain.p4truth[i-(4-j)])
	t_out.Fill()
	mgamgam.clear()
	p4gam.clear()
	mxi0.clear()
	mrecxi0.clear()		
	mlambda.clear()
	indexmc.clear()
	p4truth.clear()
	p4truthgam.clear()
#    loop through each gamma photons to reconstruct pi0 candidates
#       for l in range(chain.ngshw):
#	    for m in range(chain.ngshw):
#		if l==m:
#		    continue
#                indexgshw1 = l*6
#                indexgshw2 = m*6
#                p4shw_gam1 = ROOT.TLorentzVector(chain.p4shw[indexgshw1],chain.p4shw[indexgshw1+1],chain.p4shw[indexgshw1+2],chain.p4shw[indexgshw1+3])
#                p4shw_gam2 = ROOT.TLorentzVector(chain.p4shw[indexgshw2],chain.p4shw[indexgshw2+1],chain.p4shw[indexgshw2+2],chain.p4shw[indexgshw2+3])
#        	p4shw_gam12 = p4shw_gam1 + p4shw_gam2
#	        mass_gam12 = p4shw_gam12.M()
#                mgamgam.push_back(mass_gam12)
##		cut_pi=(mass_gam12 < 0.125 or mass_gam12 > 0.145)
##		if cut_pi:
##		    continue
#        	energy_gamma1 = p4shw_gam1.E()
#        	energy_gamma2 = p4shw_gam2.E()

#
#        	p4_xi0 = p4shw_gam12 + p4_lambda
#        	mass_xi0 = p4_xi0.M()

#
#        	p4_rec_xi0 = cms_p4 - p4_xi0
#        	rec_mass_xi0 = p4_rec_xi0.M()

#
#		t_out.Fill()
#		mgamgam.clear()

    t_out.Write()
   
    fout.Close()
    pbar.finish()
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur)
if __name__ =='__main__':
    main()
