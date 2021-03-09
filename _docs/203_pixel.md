---
title: 203 - Pixel Detector  
use_math: true
---


**Contents**
* TOC
{:toc}

## What is Pixel Detector ?


## Shockley-Ramo Theorem

  Shockley-Ramo Theorem is used to calculate the induced current on the electrode of a vacuum tube firstly, then it is also applied to calculate the induced current on electrode with fixed charges in between. Therefore, this theorem can be applied to calculate the current on the electrode of a fully depleted silicon detector.

  This Threorem is base on the classical electromagnetic theory and with the help of some mathematical formula like the Green’s first identity, it can be proved.

  Simply, we just use the theorem to calculate the current on the electrode of insterest of a fully depleted silicon detector in a few steps when a charge *q* is drifting in it.
  
  1.Remove all the fixed charge and set the targeted electrode at 1 volt with the other at 0 volt.
  
  2.Calculate the Laplace Equation that describes the scene above, and the result is called Weighting Potential $$\phi_w(x)$$ .
  
  3.Calculate the negative gradient of $$\phi_w$$, which is called Weighting Potential $$E_w(x)$$ .
  
  4.Calculate the true electric field in the detector and get the trajectory of the drifting charge using numeric method, then we know the $$V(x,t)$$ .
  
  5.Calculate the induced current on the targeted electrode: $$i(t) = E_w(x) \cdot V(x,t) \cdot q$$ .

  For more charges, we just need to add up all the carriers' contribution.

  Considering the circuit to get the waveform, we refer to the detector as a current source with a parallel capacitance that is equal to the capacitance of the detector measured through CV.

## Reference
[1]He Z . Review of the Shockley–Ramo theorem and its application in semiconductor gamma-ray detectors[J]. Nuclear Instruments & Methods in Physics Research, 2001, 463(1-2):250-267.
