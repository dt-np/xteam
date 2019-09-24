#!/usr/bin/env bash

# Main driver to submit jobs 
# Author AMIT PATHAK <amit@ihep.ac.cn>
# Created [2019-09-11 tue 14:44]

usage() {
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 

    printf "\n\t%-9s  %-40s"  "0.1"      "[run on jpsi data-09 HyperonDT]"
    printf "\n\t%-9s  %-40s"  "0.1.1"    "Split data with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.2"    "Generate Condor jobs on data 09 ---- 1..."
    printf "\n\t%-9s  %-40s"  "0.1.3"    "Test on data 09..."
    printf "\n\t%-9s  %-40s"  "0.1.4"    "Submit Condor jobs on data 09 for first 5 jobs----2"
    printf "\n\t%-9s  %-40s"  "0.1.5"    "Submit Condor jobs on data 09 for 500 jobs----3"
    printf "\n\t%-9s  %-40s"  "0.1.6"    "Submit Condor jobs on data 09 for all the jobs----4"
    printf "\n\t%-9s  %-40s"  "0.1.7"    "Check condor jobs on data 09...."
    printf "\n\t%-9s  %-40s"  "0.1.8"    "Reading the ntuples and saving them into tree/branches"
    printf "\n\t%-9s  %-40s"  "0.1.9"    "Test 1 job on data 2009 event..."

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.2"      "[running on Inclusive MC sample for HyperonDT]" 
    printf "\n\t%-9s  %-40s"  "0.2.1"    "Split MC sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.2.2"    "Generate Condor jobs on incl MC ---- 1..."
    printf "\n\t%-9s  %-40s"  "0.2.3"    "Test on inclusive MC..."
    printf "\n\t%-9s  %-40s"  "0.2.4"    "Submit Condor jobs on inclusive MC for 10 jobs----2"
    printf "\n\t%-9s  %-40s"  "0.2.5"    "Submit Condor jobs on inclusive MC for all jobs----3"
    printf "\n\t%-9s  %-40s"  "0.2.6"    "Check condor jobs on inclusive MC...."

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
    #  0.1 data-09
    # --------------------------------------------------------------------------


0.1) echo "[run on jpsi data-09 HyperonDT]"
	 ;;

    0.1.1) echo "Split data with each group 20G ..."
	   ./python/get_samples.py /besfs2/offline/data/664-1/jpsi/dst dat/run/samples/data/data_664p01_jpsi.txt 20G
	   # made 1520 groups 
    
	   ;;

    0.1.2) echo "Generate Condor jobs on data 09 ---- 1..."
	    cd /besfs/users/amitraahul/bes/hypermiss/scripts/gen_script
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/gen_script/make_jobOption_file_data09.sh ./
		cd $HOME/bes/hypermiss
        cd scripts/gen_script
        ./make_jobOption_file_data09.sh
		cd ../../dat/run/jpsi_inclusive/job_text/data
        mv jobOptions_jpsi_09-1520.txt jobOptions_jpsi_09-0.txt       
        cd $HOME/bes/hypermiss	 
        ;;

    0.1.3) echo "Test on data 09..."
        echo "have you changed test number?(yes / NO)
        ./dat/run/jpsi_inclusive/job_text/data/jobOptions_jpsi_09-0.txt"
        read opt

        if [ $opt == "yes" ]
            then 
            echo "now in yes"  
            cd dat/run/jpsi_inclusive/job_text/data
            boss.exe jobOptions_jpsi_09-0.txt
            cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change test number."
        fi
        ;;

    0.1.4) echo "Submit Condor jobs on data 09 for first 5 jobs---- 2..."
        cd dat/run/jpsi_inclusive/job_text/data
        boss.condor -g physics -n 5 jobOptions_jpsi_09-%{ProcId}.txt
        cd $HOME/bes/hypermiss
        ;;

    0.1.5) echo "Submit Condor jobs on data 09 for  500 jobs---- 3..."
        cd dat/run/jpsi_inclusive/job_text/data
        boss.condor -g physics -n 500 jobOptions_jpsi_09-%{ProcId}.txt
        cd $HOME/bes/hypermiss
        ;;

    0.1.6) echo "Submit Condor jobs on data 09 for all the jobs---- 4..."
        cd dat/run/jpsi_inclusive/job_text/data
        boss.condor -g physics -n 1520 jobOptions_jpsi_09-%{ProcId}.txt
        cd $HOME/bes/hypermiss	    
        ;;

    0.1.7) echo "Check condor jobs on data 09...."
        ./python/chk_condorjobs.py dat/run/jpsi_inclusive/rootfile_data09 500
        ;;

    0.1.8) echo "Reading the ntuples and saving them into tree/branches"
        cd HyperonDT/analysis/sigmaplus/version0.0.1/analysis_st
        ./jobdata09.sh
        cd $HOME/bes/hypermiss
        ;;

    0.1.9) echo "Test 1 job on data 2009 event..."
        ./python/sel_events.py dat/run/jpsi_inclusive/rootfile_data09/jpsi_data09-1.root dat/run/jpsi_inclusive/event_data09/jpsi_inclusive_data_event-1.root                                                              
	   ;;
   

    # --------------------------------------------------------------------------
    #  0.2 inclusiveMC  
    # --------------------------------------------------------------------------


0.2) echo "[Running on inclusiveMC data--HyperonDT]"
         ;;

    0.2.1) echo "Split MC sample with each group 20G ..."
	   ./python/get_samples.py /besfs2/offline/data/664-1/jpsi/09mc/dst dat/run/samples/inclusiveMC/mc_664p01_jpsi_09mc.txt 20G
	   # made 185 groups 
	   ;;

    0.2.2) echo "Generate Condor jobs on incl MC ---- 1..."
	    cd /besfs/users/amitraahul/bes/hypermiss/scripts/gen_script
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/gen_script/make_jobOption_file_inclusiveMC.sh ./
		cd $HOME/bes/hypermiss
        cd scripts/gen_script
        ./make_jobOption_file_inclusiveMC.sh
		cd ../../dat/run/jpsi_inclusive/job_text/inclusiveMC
        mv jobOptions_inclusive_jpsi_mc-185.txt jobOptions_inclusive_jpsi_mc-0.txt       
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

    0.2.4) echo "Submit Condor jobs on incl MC for 10 jobs---- 2..."
        cd dat/run/jpsi_inclusive/job_text/inclusiveMC
        boss.condor -g physics -n 10 jobOptions_inclusive_jpsi_mc-%{ProcId}.txt
        cd $HOME/bes/hypermiss	    
        ;;

    0.2.5) echo "Submit Condor jobs on incl MC for all jobs---- 3..."
        cd dat/run/jpsi_inclusive/job_text/inclusiveMC
        boss.condor -g physics -n 185 jobOptions_inclusive_jpsi_mc-%{ProcId}.txt
        cd $HOME/bes/hypermiss	    
        ;;
        
    0.2.6) echo "Check condor jobs on inclusive MC..."
        ./python/chk_condorjobs.py dat/run/jpsi_inclusive/rootfile_inclusiveMC 185
        ;;

esac
