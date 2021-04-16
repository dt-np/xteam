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


## Impact Ionization and Impact Ionization Model<sup>[2]</sup>

  In silicon detector, when the field in wide space charge region(wider than mean free path) is strong enough to reach a threshold, the carriers like electrons and holes can generate some electron-hole pairs through Impact Ionization. And the reciprocal of the mean free time is called the ionization coefficient $$\alpha$$. For electrons, that is $$\alpha_n$$ and the $$\alpha_p$$ is for holes, then we have the generation rate:

$$
G_{ii} = \frac{1}{q} (\alpha_n \lvert\vec{J_n}\rvert + \alpha_p \lvert\vec{J_p}\rvert)  
$$

where $$\vec{J_n}$$ and $$\vec{J_p}$$ are the electron and hole current density vectors.

There are some Impact Ionization Models and they give the ionization coefficient $$\alpha$$'s dependence on temperature and electrical field: 
  
  1. van Overstraeten – de Man Mode
  
      $$
      \alpha(F_{ava})=\gamma a exp(-\frac{\gamma b}{F_{ava}})
      $$
  
      with
  
      $$
      \gamma = \frac{tanh(\frac{\hbar \omega_{op}}{2k T_0})}{tanh(\frac{\hbar \omega_{op}}{2kT})}
      $$
  
  2. Okuto–Crowell Mode
      
      $$
      \alpha(F_{ava})=a \cdot \big (1+c(T-T_0) \big )F^{\gamma}_{ava} exp \big [ -\big (\frac{b[1+d(T-T_0)]}{F_{ava}} \big )^{\delta} \big ]
      $$
  
  3. Lackner Mode
      
      $$
      \alpha_{\mathrm{v}}\left(F_{\mathrm{ava}}\right)=\frac{\gamma a_{\mathrm{v}}}{Z} \exp \left(-\frac{\gamma b_{\mathrm{v}}}{F_{\mathrm{ava}}}\right) \text { where } v=n, p
      $$
      
      with:
      
      $$
      \begin{array}{c}
      Z=1+\frac{\gamma b_{n}}{F_{\text {ava }}} \exp \left(-\frac{\gamma b_{n}}{F_{\text {ava }}}\right)+\frac{\gamma b_{p}}{F_{\text {ava }}} \exp \left(-\frac{\gamma b_{p}} {F_{\text {ava }}}\right) \\
      \gamma=\frac{\tanh \left(\frac{\hbar \omega_{\mathrm{op}}}{2 k T_{0}}\right)}{\tanh \left(\frac{\hbar \omega_{\mathrm{op}}}{2 k T}\right)}
      \end{array}
      $$
  
  4. University of Bologna Mode
      
      The model reads:
      
      $$
      \alpha\left(F_{\text {ava }}, T\right)=\frac{F_{\text {ava }}}{a(T)+b(T) \exp \left[\frac{d(T)}{F_{\text {ava }}+c(T)}\right]}
      $$

      for electrons:
      
      $$
      a(T)=a_{0}+a_{1} t^{a_{2}} \quad b(T)=b_{0} \quad c(T)=c_{0}+c_{1} t+c_{2} t^{2} \quad d(T)=d_{0}+d_{1} t+d_{2} t^{2}
      $$
      
      for holes:
      
      $$
      \begin{array}{l}
      \qquad a(T)=a_{0}+a_{1} t \quad b(T)=b_{0} \exp \left[b_{1} t\right] \quad c(T)=c_{0} t^{c_{1}} \quad d(T)=d_{0}+d_{1} t+d_{2} t^{2} \\
      \text { where } t=T / 1 \mathrm{~K} .
      \end{array}
      $$
      
  5. the new University of Bologna Mode
      
      $$
      \alpha\left(F_{\text {ava }}, T\right)=\frac{F_{\text {ava }}}{a(T)+b(T) \exp \left[\frac{d(T)}{F_{\text {ava }}+c(T)}\right]}
      $$
      
      $$
      a(T)=\sum_{k=0}^{3} a_{k}\left(\frac{T}{1 \mathrm{~K}}\right)^{k}, \quad b(T)=\sum_{k=0}^{10} b_{k}\left(\frac{T}{1 \mathrm{~K}}\right)^{k}, \quad c(T)=\sum_{k=0}^{3} c_{k}\left(\frac{T}{1 \mathrm{~K}}\right)^{k}, \quad d(T)=\sum_{k=0}^{3} d_{k}\left(\frac{T}{1 \mathrm{~K}}\right)^{k}
      $$
  
  6. Hatakeyama Mode
      
      $$
      \begin{array}{c}
      \alpha=\gamma a e^{-\frac{\gamma b}{F}} \\
      \gamma=\frac{\tanh \left(\frac{\hbar \omega_{\mathrm{op}}}{2 k T_{0}}\right)}{\tanh \left(\frac{\hbar \omega_{\mathrm{op}}}{2 k T}\right)}
      \end{array}
      $$
      
      $$
      F^{2}=F_{0001}^{2}+F_{11 \overline{2} 0}^{2}
      $$

      $$
      B=\frac{F}{\sqrt{\left(\frac{F_{11 \overline{2} 0}}{b_{11 \overline{2} 0}}\right)^{2}+\left(\frac{F_{0001}}{b_{0001}}\right)^{2}}}
      $$
      
      $$
      a=a_{11 \overline{2} 0}^{\left(\frac{B F_{1120}}{b_{11 \overline{2} 0} F}\right)^{2}} a_{0001}^{\left(\frac{B F_{0001}}{b_{0001} F}\right)^{2}}
      $$
      
      $$
      \begin{array}{c}
      A=\log \frac{a_{0001}}{a_{11\overline{2} 0} } \\
      b=B \sqrt{1-\theta A^{2}\left(\frac{B F_{11 \overline{2} 0} F_{0001}}{F b_{11 \overline{2} 0} b_{0001}}\right)^{2}}
      \end{array}
      $$

**Reference**

[2] Sentaurus™ Device UserGuide Version P-2019.03, March 2019
