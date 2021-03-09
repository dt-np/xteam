---
title: 302 - MacOS Tips
---


**Contents**
* TOC
{:toc}


## Install ROOT from source 

1. Download the ROOT source into $HOME/local/share/
2. Unpack with 'tar xf root-6.10.06.tar.gz'
3. $ cd root-6.10.06/build
4. $ cmake .. 
5. $ make -j4 
6. $ . ~/local/share/root-6.10.06/bulid/bin/thisroot.sh 
7. $ root 

Note: step 4. : if the cmake is not in the default path, add this line to the .bashrc: 

	export PATH=/Applications/Cmake.app/Contents/bin:$PATH 

## Install ROOT from dmg
1. Download the ROOT dmg file
2. Double click and install 
3. $ source /Applications/root_v6.14.04/bin/thisroot.sh


## Install   Emacs  

1. Download the source file into $HOME/tmp 
2. Unpack with 'tar xf emacs-25.3.tar.xz'  
3. $ cd emacs-25.3
4. $ ./configure  --with-ns 
5. $ make -j4 
6. $ make install 
7. $ open nextstep 
8. Drag the Emacs App into the 'Applications' location 


## Change hostname 

From this link [1]: 

	$ sudo scutil --set HostName "newname"

[1]: https://apple.stackexchange.com/questions/66611/how-to-change-computer-name-so-terminal-displays-it-in-mac-os-x-mountain-lion