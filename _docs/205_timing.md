---
title: 205 - Timing Detector  
---

**Contents**
* TOC
{:toc}

## What is Timing Detector ?
## Time resolution of 3D semiconductor

<img src="/images/3D_SiC_structure.png" width="400"/>

The time resolution of a detector is to a large extent given by jitter contribution and time walk contribution.  

1.Time work contribution is determined by the ratio of the rise time of the signal waveform and signal to noise ratio. Due to the sensor cell of 3D sensor is only about 30 um, the rise time is small. When the signal to noise ratio is small, the jitter contribution to time resolution is relatively more important and possibly even dominant. When the signal to noise is enough (like Low Gain Avalanche Detectors (LGAD)), the jitter contribution can be ignored.

2. The time work contribution is caused by the difference in signal height and signal shapes. 
- The difference in signal height can be reduced by using Constant Fraction Discrimination. 
- The signal shapes are mainly affected by the differences in drift paths (depending on the git position inside the pixel cell) of generated carriers, which drift with different drift velocities in different weighting fields. Fluctuations in ionization rates along the track path (Landau fluctuations) add to the differences in pulse shapes. In 3D detectors, Landau fluctuations are less important as charges generated at different depths have the same drift distance to the collection electrode. The time walk contribution is therefore dominated by the location of impact within the cell.

The conclusion is that the time resolution of 3D semiconductor sensor is mainly given by the location of impact within the sensor when the signal to noise ratio is large enough.

**Reference**

[1]G. Kramberger et al. Timing performance of small cell 3D silicon detectors. .[DOI: 10.1016/j.nima.2019.04.088].(https://pdf.sciencedirectassets.com/271580/1-s2.0-S0168900219X00157/1-s2.0-S0168900219305704/main.pdf?X-Amz-Security-Token=IQoJb3JpZ2luX2VjEMn%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJHMEUCIBZFEU7N1g3dHPsOeQJg1%2FV5Kc620exkbVUCMnxgbAFFAiEAmbLA1Bzj20zdbBD3TEtHaBuopskdJV1HRSrGX%2F96jT0qvQMI4v%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FARADGgwwNTkwMDM1NDY4NjUiDPXsGmRzDSzUdSlKDiqRA9qxqhCDVcBz1BI98X7wiyOtbUHCOahkeGRJeuCdHgNzylxYcVl3SObAvp%2FpqQBJlAkJYj9Na3KVjhuE7blOBBrR6gD47Ofm0TqD4d9N78igoW32bGfEz%2B2xxQUdDJP0sBgyFtoWgIw8OR6AF5Do3wgIWUMC%2BkDTDWOs5nxFz%2B10wer5GudHI5fqA6TsKqM05TDBg0i242ePe1Gc8J7RDXGNNM90ug6%2FSMVCoMdb2HAIMkQQUkinWD3bYnNTKnNZ%2BIBwjWoizWx%2B2cfgJdiYGGhvzfpDUBcwfN6Or4%2BQwHWVsjBdiJ3meN8ctat1rLtb9B1yFipmgbm7gxBtqP8opUI6lVX5Hb5dsyCvf8lm9iaAD%2FaJ2zZBnAOJy5XWSLKDGbTwGc4eIdtr1WdqpAnjOnuR6NN8QcKJ3NguiFHPjIZayh8sVO0hDdUc4TD%2BydqsDyqzuHIP1IwO5aChzvnCAqTWQMq5k%2BBtHo8LHzX%2F8ySmhKufDkUAH2QhkyyaRwwb74%2F8f%2BPqkwcc7sMZr0qV89s6MJn%2BhYIGOusB5qYRIsQdZR0szX6Frh7d%2BiPalREw9Lb9f0%2Brow7kBRtf0%2F%2FIW0ZFqi%2F3S0KM2auwHL7k0l%2FtE9gmf5AI7swohvG5KCAkT1XowljL4I9MjIaYQWtLJW7pY8BdyLk1n2saRaB1by7SZwSk69xqu8bNSYNWMnGvsko8R%2FnYdtmOrwl80wMwMRJlelSa3AnbAiKKTmNo5egNwcOFacfaPg7ZrF%2FkYuSlBLIwBrBjlIY7MK4ZGaiW6hRGTKKYr0IN0lQ5jLRftchII6O2t0QjTHmJqKd7Y0psbD9VDHfwY8uBBv%2BfjXIlTCXf2g4nsA%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20210305T012021Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAQ3PHCVTYXI6B55LB%2F20210305%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=d7e91c698a67d33d276f468bfdbf5ff78ceef2c17dc61fdaaffb3f09448935ef&hash=de89b3e9da95d19ca264714d91790f1c4c9032ff41f4328b1ed88573508a0ba0&host=68042c943591013ac2b2430a89b270f6af2c76d8dfd086a07176afe7c76c2c61&pii=S0168900219305704&tid=spdf-91fe080d-a156-4b52-bc65-a86b07800483&sid=7b5f82eb68cac7489a4ba7c7eb6247288e51gxrqa&type=client)
