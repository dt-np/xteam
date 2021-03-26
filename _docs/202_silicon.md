---
title: 202 - Silicon Detector  
use_math: true
---

**Contents**
* TOC
{:toc}

## What is Silicon Detector ?

Semiconductor is a kind of material with conductivity between metal and insulator. It is located in group IV(C, Si,  Ge and their compounds) or III-V(compound of them, like GaAs) of the periodic table of elements and compound semiconductor materials, which are widely used in detectors, integrated circuits and other fields. 
The commonly used semiconductor detectors are p-n junction semiconductor detector, lithium drift semiconductor detector and high purity germanium semiconductor detector. And another interface which is similar to p-n junction is Schottky junction or Schottky barrier, connected metal with semiconductor. 

<a href="/images/element_table.jpg">
<img src="/images/element_table.jpg" width="400"/>
</a>

Here we introduce some details about p-n junction semiconductor, formed by the contact of p-type semiconductor and n-type semiconductor. or metal and semiconductor.

Due to the different carrier concentrations on both sides, the electrons in the N region diffuse to the p region, the positively charged donor ions stay in the N region, the holes in the p region diffuse to the N region, and the negatively charged acceptor ions stay in the p region. The net positive charge of N region, P region and net negative charge induce a built-in electric field near the metallurgical junction, and the direction is from n region to p region. We can see clearly the net positive charge and net negative charge regions formed in the semiconductor. Since there is no movable charge in this region, it is called space charge region or depletion region. There is still a concentration gradient at the edge of the depletion region, and most carriers are subjected to a "diffusion force".
At the same time, most carriers are also affected by the electric field force in the depletion region, which is opposite to the "diffusion force".


## Shockley-Ramo Theorem[1]

  Shockley-Ramo Theorem is used to calculate the induced current on the electrode of a vacuum tube firstly, then it is also applied to calculate the induced current on electrode with fixed charges in between. Therefore, this theorem can be applied to calculate the current on the electrode of a fully depleted silicon detector.

  This Threorem is base on the classical electromagnetic theory and with the help of some mathematical formula like the Green’s first identity, it can be proved.

  Simply, we just use the theorem to calculate the current on the electrode of insterest of a fully depleted silicon detector in a few steps when a charge *q* is drifting in it.
  
  1. Remove all the space charge and set the targeted electrode at 1 volt with the other at 0 volt.
  
  2. Calculate the Laplace Equation that describes the scene above, and the result is called Weighting Potential $$\phi_w(\vec{x})$$ .
  
  3. Calculate the negative gradient of $$\phi_w$$, which is called Weighting Field $$\vec{E_w}(\vec{x})$$ .
  
  4. Calculate the true electric field in the detector and get the trajectory of the drifting charge using numeric method, then we know the $$\vec{v}(\vec{x},t)$$ .
  
  5. Calculate the induced current on the targeted electrode: $$i(t) = \vec{E_w}(\vec{x}) \cdot \vec{v}(\vec{x},t) \cdot q$$ .

  For more charges, we just need to add up all the carriers' contribution.

  Considering the circuit to get the waveform, we refer to the detector as a current source with a parallel capacitance that is equal to the capacitance of the detector measured through CV.

 **Reference**
 
[1]He Z . Review of the Shockley–Ramo theorem and its application in semiconductor gamma-ray detectors[J]. Nuclear Instruments & Methods in Physics Research, 2001, 463(1-2):250-267.  <http://cztlab.engin.umich.edu/wp-content/uploads/sites/187/2015/03/ShockleyRamo.pdf>
