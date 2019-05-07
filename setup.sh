#!/usr/bin/env bash

# Main driver to setup the environment 
# Author AMIT PATHAK <amit@ihep.ac.cn>
# Created [2019-05-06 Mon 07:58]


usage() {
    printf "NAME\n\tsetup.sh - Main driver to setup the environment \n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "source setup.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-20s  %-40s"  "init-boss-7.0.4"      "initialise the boss 7.0.4"
    printf "\n\t%-20s  %-40s"  "boss-7.0.4"           "setup the boss 7.0.4"
    printf "\n\n" 
}
if [[ $# -eq 0 ]]; then
    usage
    echo "Please enter your option: "
    read option
else
    option=$1    
fi

case $option in
    
    # --------------------------------------------------------------------------
    #  Boss 7.0.4  
    # --------------------------------------------------------------------------

    init-boss-7.0.4) echo "Setting the environment for BOSS 7.0.4..."
    
    cp -r /afs/ihep.ac.cn/bes3/offline/Boss/cmthome/cmthome-7.0.4/ ./

    echo "set WorkArea \"\$(HOME)/bes/hypermiss\"" >> cmthome-7.0.4/requirements
    echo "path_remove CMTPATH  \"\${WorkArea}\"" >> cmthome-7.0.4/requirements
    echo "path_prepend CMTPATH  \"\${WorkArea}\"" >> cmthome-7.0.4/requirements

    cd cmthome-7.0.4
    source setupCMT.sh
    cmt config
    source setup.sh

    cd ../TestRelease/TestRelease-00-00-84/cmt
    
    cmt br cmt config
    cmt br gmake
    cd - 
    cd .. 
    ;; 

    boss-7.0.4) echo "Settingup boss 7.0.4"

    cd cmthome-7.0.4
    source setupCMT.sh
    cmt config
    source setup.sh

    cd ../TestRelease/TestRelease-00-00-84/cmt
    source setup.sh
    cd ../../../
    
    ;;

esac    
