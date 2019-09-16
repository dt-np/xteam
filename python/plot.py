#!/usr/bin/env python
"""
Generate plots
"""

__author__ = "AMIT PATHAK <amit@ihep.ac.cn>"
__copyright__ = "Copyright (c) AMIT PATHAK"
__created__ = "[2019-07-22 Tue 15:00]"

import ROOT
from ROOT import gStyle, TCanvas, TString, TChain, TStyle
from ROOT import TH1D, TFile, TLegend

f = ROOT.TFile.Open('../run/root_jpsiantisigmaminussigmaplus/jpsiantisigmaminussigmaplus_gen_mc.root', 'read')
canvas = ROOT.TCanvas('canvas','',500,500)
tr1 = f.Get('tree')
tr1.Draw('vr0')
canvas.SaveAs('../run/plots/Plot.pdf')
f.Print()
f.Close()
