#!/usr/bin/env bash

# Main driver to submit jobs 
# Author AMIT PATHAK <amit@ihep.ac.cn>
# Created [2019-05-07 tue 09:44]

usage() {
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 

    printf "\n\t%-9s  %-40s"  "0.1"      "[run on HyperonDT]"
    printf "\n\t%-9s  %-40s"  "0.1.1"    "Preselection for 10 events -- generate root file [Checking interactively]..."
    printf "\n\t%-9s  %-40s"  "0.1.2"    "Preselection for 20k events -- generate root file [cluster job]..."
    
    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.2"      "[running on Inclusive MC sample for HyperonDT]" 
    printf "\n\t%-9s  %-40s"  "0.2.1"    "Split MC sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.2.2"    "Generate Condor jobs on incl MC ---- 1..."
    printf "\n\t%-9s  %-40s"  "0.2.3"    "Test on inclusive MC..."
    printf "\n\t%-9s  %-40s"  "0.2.4"    "Submit Condor jobs on inclusive MC ----2"


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
    #  0.1 MC  
    # --------------------------------------------------------------------------


0.1) echo "[run for HyperonDT]"
	 ;;

    0.1.1) echo "Preselection for 10 events -- generate root file [Checking interactively]..."

        echo "have you changed event number to 10 for interactive job?(yes / NO)"
        
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"
        
        cd /besfs/users/amitraahul/bes/hypermiss/scripts/gen_script
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/gen_script/jobOptions_hyperon_gen_mc.txt ./
	    boss.exe jobOptions_hyperon_gen_mc.txt
        cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change the event number"
        fi
        ;;
        
    0.1.2) echo "Preselection for 20k events -- generate root file [cluster job]..."
	
        echo "have you changed event number from 10 which was previously set for interactive job?(yes / NO)"
        
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"

        cd /besfs/users/amitraahul/bes/hypermiss/scripts/gen_script
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/gen_script/jobOptions_hyperon_gen_mc.txt ./
	    boss.condor -g physics jobOptions_hyperon_gen_mc.txt
        cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change the event number"
        fi
        ;;

   
    # --------------------------------------------------------------------------
    #  0.2 MC  
    # --------------------------------------------------------------------------


0.2) echo "[Running on data--HyperonDT]"
         ;;

    0.2.1) echo "Split MC sample with each group 20G ..."
	   ./python/get_samples.py /besfs2/offline/data/664-1/jpsi/09mc/dst dat/run/samples/inclusiveMC/mc_664p01_jpsi_09mc.txt 20G
	   # made 394 groups 
	   ;;

    0.2.2) echo "Generate Condor jobs on incl MC ---- 1..."
	    cd /besfs/users/amitraahul/bes/hypermiss/scripts/gen_script
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/gen_script/make_jobOption_file_inclusiveMC.sh ./
		cd $HOME/bes/hypermiss
        cd scripts/gen_script
        ./make_jobOption_file_inclusiveMC.sh
		cd ../../dat/run/jpsi_inclusive/job_text/inclusiveMC
        mv jobOptions_inclusive_jpsi_mc-394.txt jobOptions_inclusive_jpsi_mc-0.txt       
        cd $HOME/bes/hypermiss	 
        ;;

    0.2.3) echo "Test on incl MC..."
        echo "have you changed test number?(yes / NO)
        ./dat/run/jpsi_inclusive/job_text/inclusiveMC/jobOptions_inclusive_jpsi_mc-0.txt"
        read opt
        if [ $opt == "yes" ]
            then 
            echo "now in yes"  
            cd dat/run/jpsi_inclusive/job_text/inclusiveMC
            boss.exe jobOptions_inclusive_jpsi_mc-0.txt
            cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change test number."
        fi
        ;;

    0.2.4) echo "Submit Condor jobs on incl MC ---- 2..."
        cd dat/run/jpsi_inclusive/job_text/inclusiveMC
        boss.condor -g physics -n 394 jobOptions_inclusive_jpsi_mc-%{ProcId}.txt
        cd $HOME/bes/hypermiss	    
        ;;

    0.2.5) echo "Check condor jobs on inclusive MC..."
        ./python/chk_condorjobs.py dat/run/jpsi_inclusive/rootfile_inclusiveMC 394
        ;;

esac
