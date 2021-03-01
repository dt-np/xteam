---
title: 301 - Linux Tips
---


**Contents**
* TOC
{:toc}


## Install ROOT as User 

$ cd ~/tmp 

$ wget  https://root.cern.ch/download/root_v5.34.36.source.tar.gz  #download root files

$ tar xf root_v5.34.36.source.tar.gz                               #Decompression files

$ cd root

$ ./configure --prefix=$HOME/local                                 #check 

$ make                                     #Corresponding to include

$ make install 



