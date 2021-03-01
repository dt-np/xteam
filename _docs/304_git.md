---
title: 304 - Git Usage 
---


**Contents**
* TOC
{:toc}


## Set the username and e-mail address 

    $ git config --global user.name "Firstname Lastname"
    $ git config --global user.email "your_email@example.com"
    $ git config --global color.ui auto

## Register github account on github.com

 - Create SSH key:

    $ ssh-keygen -t rsa -C "your_email@example.com"
    Generating public/private rsa key pair.
    Enter file in which to save the key
    (/Users/your_user_directory/.ssh/id_rsa):
    Enter passphrase (empty for no passphrase):
    Enter same passphrase again:
    Enter $ cat ~/.ssh/id_rsa.pub and copy the SSH key

Github.com -> Settings -> SSH and GPG keys -> New SSH keys, then paste the key

    $ ssh -T git@github.com

Clone jadepix to your computer: 

    $ git clone git@github.com:cepc/jadepix.git

Make what you forked synchronize with the original one [1]:

    git remote add upstream git@github.com:cepc/jadepix.git
    git fetch upstream
    git merge upstream/master
    git push origin master

[1]: http://blog.csdn.net/myuantao3286286/article/details/50477139
