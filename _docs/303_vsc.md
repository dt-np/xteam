---
title: 303 - VS Code
---


**Contents**
* TOC
{:toc}


## General Info 

We recommend team members to use VSCode for major programing tasks.  

<https://code.visualstudio.com>

Source code development at: <https://github.com/Microsoft/vscode>

 

## Remote Edit 

<https://codepen.io/ginfuru/post/remote-editing-files-with-ssh>


* Server side configuration 

On remote Linux server: 


1. Make sure your $PATH include your $HOME/local/bin: 
Add this line in your $HOME/.bashrc file: 	
```
	export PATH=$HOME/local/bin:$PATH 
```
2. Download rmate and change to rcode: 
```
	$ cd $HOME/local/bin
	$ wget  https://raw.github.com/aurora/rmate/master/rmate
	$ mv rmate rcode 
	$ chmod u+x rcode 
``` 

* Local side configuration 

1. Install remote-vscode: 
	In the Extensions, search "Remote VSCode" and install. 
	You may need to restart the VSCode after intall 

2. Start the remote server:
[Mac]  "Shift+cmd+p" > Remote: Start Server 
[Windows/Linux] "Shift + Ctrl + p" > Remote: Start Server  

3. [Windows] install OpenSSH:
	Install [OpenSSH](http://www.mls-software.com/opensshd.html)
	Set Path :  C:\Program Files\OpenSSH\bin (depend on your install path)

4. Config local ssh RemoteForward: 
	[Mac] ~/.ssh/config
	[Windows] C:\Users\username\.ssh\config

	```
	Host myRemoteServerName
    	RemoteForward <my-port-number> localhost:52698
	```

### Remote Open files 

After above settings, you can do the remote edit.
 
Use any terminal which can do the ssh, (here we recommend you use the integrated terminal in VSCode, by typing Ctrl + ` on both Mac and Windows. 

```
$ ssh user@remote.org 
[Windows7/Linux]  $ssh -R <my-port-number>:localhost:52698 user@example.org
$ rcode -p  <my-port-number> example_program(you can change port number to be yourself number in $HOME/local/bin/rcode, if you want to use command "rcode example_program" to open a file)
```

This should open this example_program file on your local VSCode. 


### Resolving conflict for multiple users  

Conflict port number [1]: 

Note: Different people need to set a different  <my-port-number> by yourself, if you have setted your own  <my-port-number>, please register in the following form and others cannot use it anymore.

* CEPCVTX.ihep.ac.cn

| Name           | Port Number       |
| -------------- | ----------------- |
| JING, Maoqiang | 52689             |
| YANG Tao       | 52691/54321/12345 |
| SHI Xin        | 52699             |
| KONG Lingteng  | 56666             |
| ZENG Hao       | 55555             |
	

* lxslc.ihep.ac.cn

| Name          | Port Number |
| ------------- | ----------- |
| SHI Xin       | 52699       |
| XIAO Suyu     | 55555       |
| YANG Yuzhen   | 52600       |
| XIAO Suyu-Mac | 55556       |
| Yang Tao      | 54321       |
| Amit Pathak	| 52700	      |
| Tan Yuhang	| 59637       |
 	
	ssh -Y -R xxxxx:127.0.0.1:52698 username@lxslc6.ihep.ac.cn

Solve the conflict:
In mac:
	
	$ vi  ~/.ssh/config

Change the last line as(if for Yuzhen):

	RemoteForward 52600 127.0.0.1:52698

In home of lxslc.ihep.ac.cn

	$ vi ~/local/bin/rcode

Change the port info as(if for Yuzhen):

 	default configuration
	host=localhost
	port=52600


## VSCode in terminal 

<https://stackoverflow.com/questions/30065227/run-open-vscode-from-mac-terminal>

[Mac] Cmd+shift+p:   > Shell Command: Install code in PATH 


## PDF Plugin 

To preview pdf file, install extension vscode-pdf in Vscode. 

Then open the pdf with code (or rcode) from terminal. 

## File EOL 

Solution  : /usr/bin/env: ‘python\r’: No such file or directory

VScode for Chinese version：
文件->首选项->设置->文件
Change ''file.eol'' : ''\r\n'' -> ''file.eol'' : ''\n''


[1]: https://ernie.io/2011/12/12/textmate-2-rmate-awesome/

## Run VSCode in Docker

Install Docker fisrt: <https://www.docker.com/get-started>

Then, running a Linux image in a container. If you do not have one, you can try 
	
	$ docker pull debian 

to get a debian image for docker.

Running this image in a container: 

	$ docker run -it -e DISPLAY=host.docker.internal:0.0 debian (for Windows CMD)

	$ docker run -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix/:/tmp/.X11-unix debian (for Linux)

"DISPLAY=" sets the GUI, "debian" is the image I run here, you can substitute it with yours.

(
For the debian image above we need to install some tools like wget and gpg, at first you are in root mode without the other users:
	
	$ apt update

	$ apt install wget

	$ apt install gpg
	
	$ apt install x-window-system-core
	
	$ apt install libasound2


)

Next step, install VSCode in the container: <https://code.visualstudio.com/docs/setup/linux>

Windows will need a software to receive the GUI, before you open the GUI you should run this on your Windows fisrt: vcxsrv <https://sourceforge.net/projects/vcxsrv/>

Then, start VSCode in the container:

	$ code (normal user mode)
	
	$ code --user-data-dir (if you are in root mode)

Actually, It can be applied to all the software with GUI. The key point is to find the DISPLAY=? to use X11.
