---
title: 202 - Silicon Detector  
use_math: true
---

**Contents**
* TOC
{:toc}

## What is Silicon Detector ?


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


## Impact Ionization and Impact Ionization Model[2]</sup>

  In silicon detector, when the field in wide space charge region(wider than mean free path) is strong enough to reach a threshold, the carriers like electron and holes can generate some electron-hole pairs through Impact Ionization. And the reciprocal of the mean free time is called the ionization coefficient $$\alpha$$. For electrons, that is $$\alpgha_n$$ and the $$\alpha_p$$ is for holes, then we have the generation rate:

$$
G_{ii} = 1/q (\alpha_n abs(\vector{J_n}) + \alpha_p abs(\vector{J_p}))  
$$

where $$\vector{J_n}$$ and $$\vector{J_p}$$ are the electron and hole current density vectors.

There are some Impact Ionization Models: 
  1. van Overstraeten – de Man Mode
  2. Okuto–Crowell Mode
  3. Lackner Mode
  4. University of Bologna Mode
  5. the new University of Bologna Mode
  6. Hatakeyama Mode

**Reference**

[2] Sentaurus™ Device UserGuide Version P-2019.03, March 2019
