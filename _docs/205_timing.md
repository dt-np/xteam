---
title: 205 - Timing Detector  
---

**Contents**
* TOC
{:toc}

## What is Timing Detector ?
## Time resolution of 3D semiconductor
<img src="/images/3D_SiC_structure.png" width="400"/>
The time resolution of a detector is to a large extent given by jitter contribution and time work contribution.  
- Time work contribution is determined by the ratio of the rise time of the signal waveform and signal to noise ratio. Due to the sensor cell of 3D sensor is only about 30 um, the rise time is small and the contribution of jitter contribution can be ignored in 3D semiconductor sensor. 
- The time work contribution is caused by the difference in signal height and signal shapes. 
- - The difference in signal height can be reduced by using Constant Fraction Discrimination. 
- - The signal shapes are mainly affected by the differences in drift paths (depending on the git position inside the pixel cell) of generated carriers, which drift with different drift velocities in different weighting fields. Fluctuations in ionization rates along the track path (Landau fluctuations) add to the differences in pulse shapes. In 3D detectors, Landau fluctuations are less important as charges generated at different depths have the same drift distance to the collection electrode. The time walk contribution is therefore dominated by the location of impact within the cell.
The conclusion is that the time resolution of 3D semiconductor sensor is mainly given by the location of impact within the cell.
