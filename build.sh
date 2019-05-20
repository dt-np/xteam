#!/usr/bin/env bash

# Main driver to build programs
# Author PATHAK Amit <amit@ihep.ac.cn>
# Created [2019-05-17 Fri 10:34]


usage() {
    printf "NAME\n\tbuild.sh - Main driver to build programs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./build.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-5s  %-40s\n"  "1"  "build jpsiantisigmaminussigmaplus analyzer" 

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
    1) echo "Building jpsiantisigmaminussigmaplus module..."
    cd Analysis/Physics/jpsiantisigmaminussigmaplus/jpsiantisigmaminussigmaplus-00-00-01/cmt
       gmake  
       ;;
esac
