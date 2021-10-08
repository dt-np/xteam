---
title: RASER 
use_math: true  
---

**Contents**
* TOC
{:toc}


## Introduction 

**RA**diation **SE**miconducto**R** 


## UserGuide 

### Planner 3D  
- An example python code to use raser:

> $ python example.py det_model=planar3D parfile=setting.json
 
 - example.py 

```python 
import raser
args = sys.argv[1:]
dset = raser.Setting(args)

my_d = raser.R3dDetector(dset)
my_f = raser.FenicsCal(my_d, dset.fenics)
my_g4p = raser.Particles(my_d, my_f, dset)
my_current = raser.CalCurrent(my_d, my_f, my_g4p, dset)
ele_current = raser.Amplifier(my_d, dset.amplifer)
```
 - setting.json 
  
```json
[{
"steplength" : "1",
"name" : "planar3D",

"lx" : "50",
"ly" : "50",
"lz" : "10",
"doping" : "10", 
"voltage" : "-100",
"temp" : "300.0",

"mesh" : "32",
"xyscale" : "1",

"maxstep" : "10",
"g4_vis" : "0",
"par_inx" : "25",
"par_iny" : "25",
"par_inz" : "17000",
"par_outx" : "25",
"par_outy" : "25",
"par_outz" : "0",

"t_rise" : "1",
"t_fall" : "1",
"trans_imp" : "1",
"CDet" : "1",
"BBW" : "1",
"BBGain" : "10",
"BB_imp" : "1",
"OscBW" : "1"
}]
```

###  TCT Simulation 
> $ python example.py det_model=silicon_lgad2D parfile=setting.json laser_model=TPA laser_file=laser.json

 - example.py 

```python 
import raser
args = sys.argv[1:]
dset = Setting(args)

my_d = R2dDetector(dset.detector)
my_f = FenicsCal2D(my_d)
my_l = TCTTracks(my_d,dset.laser)
my_l.getTrackProfile2D(0.5,0.5,0.5)
my_current = CalCurrent2DTCT(my_l,my_f,my_d)
ele_current = Amplifier(my_d, dset.amplifer)
```

 - laser.json

```json
[{
"laser_model" : "TPA",
"direction" : "edge",

"alpha" : 987,
"beta_2" : 1.5E-11,
"refractionIndex" : 3.51,

"wavelength" : 1.55e-6,
"tau" : 60e-15,
"power" : 5e-11,
"widthBeamWaist" : 1e-6,
"l_Rayleigh" : 15.7e-6,

"r_step" : 1,
"h_step" : 10
}]
```
## Detector Physics 

## Computing Algorithm 

## Development History 

## Acknowledgment 

## References 


