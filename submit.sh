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
    printf "\n\t%-9s  %-40s"  "0.1.5"    "Check condor jobs for 5 jobs on data 09...."
    printf "\n\t%-9s  %-40s"  "0.1.6"    "Submit Condor jobs on data 09 for all the 388 jobs----4"
    printf "\n\t%-9s  %-40s"  "0.1.7"    "Check condor jobs on data 09 for all the jobs...."
    printf "\n\t%-9s  %-40s"  "0.1.8"    "Test 1 job on data 2009 event..."
    printf "\n\t%-9s  %-40s"  "0.1.9"    "Generate Condor jobs on data 2009 event ---- 1"
    printf "\n\t%-9s  %-40s"  "0.1.10"    "Submit Condor jobs on data 2009 event ---- 2"
    printf "\n\t%-9s  %-40s"  "0.1.11"    "Check Condor jobs on data 2009 event..."
    printf "\n\t%-9s  %-40s"  "0.1.12"     "Merge rootfile on data 2009 event..."
    printf "\n\t%-9s  %-40s"  "0.1.13"     "Generate plot for mgamgam..."

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.2"      "[running on Inclusive MC sample for HyperonDT]" 
    printf "\n\t%-9s  %-40s"  "0.2.1"    "Split MC sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.2.2"    "Generate Condor jobs on incl MC ---- 1..."
    printf "\n\t%-9s  %-40s"  "0.2.3"    "Test on inclusive MC..."
    printf "\n\t%-9s  %-40s"  "0.2.4"    "Submit Condor jobs on inclusive MC for 10 jobs----2"
    printf "\n\t%-9s  %-40s"  "0.2.5"    "Check condor jobs on inclusive MC for 10 jobs----2"
    printf "\n\t%-9s  %-40s"  "0.2.6"    "Submit Condor jobs on inclusive MC for all 185 jobs----3"
    printf "\n\t%-9s  %-40s"  "0.2.7"    "Check condor jobs on inclusive MC...."
    printf "\n\t%-9s  %-40s"  "0.2.8"    "Test 1 job on inclusive MC event..."
    printf "\n\t%-9s  %-40s"  "0.2.9"    "Generate Condor jobs on inclusive MC event ---- 1"
    printf "\n\t%-9s  %-40s"  "0.2.10"    "Submit Condor jobs on inclusive MC event ---- 2"
    printf "\n\t%-9s  %-40s"  "0.2.11"    "Check Condor jobs on inclusive MC event..."
    printf "\n\t%-9s  %-40s"  "0.2.12"     "Merge rootfile on inclusive MC event..."
    printf "\n\t%-9s  %-40s"  "0.2.13"     "Generate plot for mgamgam..."

    printf "\n\t%-9s  %-40s"  "0.3"      "[run on signal MC for Xi0]"
    printf "\n\t%-9s  %-40s"  "0.3.1"    "simulation --10 signal MC sample interactively for Xi0 events..."
    printf "\n\t%-9s  %-40s"  "0.3.2"    "Generate -- 20000 Xi0 MC signal..."
    printf "\n\t%-9s  %-40s"  "0.3.3"    "Reconstruction -- 20000 Xi0 MC signal..."
    printf "\n\t%-9s  %-40s"  "0.3.4"    "Preselection for 10 events -- generate root file [Checking interactively]..."
    printf "\n\t%-9s  %-40s"  "0.3.5"    "Preselection for 20k events -- generate root file [cluster job]..."
    printf "\n\t%-9s  %-40s"  "0.3.6"     "Select events on signal MC sample..."
    printf "\n\t%-9s  %-40s"  "0.3.7"     "Generate plot for mgamgam..."

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
    # -----------------------------------------------------------------------

0.1) echo "[run on jpsi data-09 HyperonDT]"
	 ;;

    0.1.1) echo "Split data 09 with each group 20G ..."
	   ./python/get_samples.py /besfs2/offline/data/664-1/jpsi/dst dat/run/samples/data09/data_664p01_jpsi.txt 20G
	   # made 388 groups 
    
	   ;;

    0.1.2) echo "Generate Condor jobs on data 09 ---- 1..."
	    cd /besfs/users/amitraahul/bes/hypermiss/scripts/gen_script
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/gen_script/make_jobOption_file_data09.sh ./
		cd $HOME/bes/hypermiss
        cd scripts/gen_script
        ./make_jobOption_file_data09.sh
		cd ../../dat/run/jpsi_inclusive/job_text/data09
        mv jobOptions_jpsi_09-388.txt jobOptions_jpsi_09-0.txt
        cd $HOME/bes/hypermiss	 
        ;;

    0.1.3) echo "Test on data 09..."
        echo "have you changed test number?(yes / NO)
        ./dat/run/jpsi_inclusive/job_text/data09/jobOptions_jpsi_09-0.txt"
        read opt

        if [ $opt == "yes" ]
            then 
            echo "now in yes"  
            cd dat/run/jpsi_inclusive/job_text/data09
            boss.exe jobOptions_jpsi_09-0.txt
            cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change test number."
        fi
        ;;

    0.1.4) echo "Submit Condor jobs on data 09 for first 5 jobs---- 2..."
        cd dat/run/jpsi_inclusive/job_text/data09
        boss.condor -g physics -n 5 jobOptions_jpsi_09-%{ProcId}.txt
        cd $HOME/bes/hypermiss
        ;;
    
    0.1.5) echo "Check condor jobs for 5 jobs on data 09...."
        ./python/chk_condorjobs.py dat/run/jpsi_inclusive/rootfile_data09 5
        ;;

    0.1.6) echo "Submit Condor jobs on data 09 for all the 388 jobs---- 3..."
        cd dat/run/jpsi_inclusive/job_text/data09
        boss.condor -g physics -n 388 jobOptions_jpsi_09-%{ProcId}.txt
        cd $HOME/bes/hypermiss	    
        ;;

    0.1.7) echo "Check condor jobs on data 09 for all the jobs...."
        ./python/chk_condorjobs.py dat/run/jpsi_inclusive/rootfile_data09 388
        ;;

    0.1.8) echo "Test 1 job on data 2009 event..."
        ./python/sel_events.py dat/run/jpsi_inclusive/rootfile_data09/jpsi_data09-1.root dat/run/jpsi_inclusive/event_data09/jpsi_data09_event-1.root                                                              
	   ;;
    
    0.1.9) echo "Generate Condor jobs on data 2009 event ---- 1..."
        mkdir -p dat/run/jpsi_inclusive/job_text/data09_event
        cd scripts/gen_script
        ./make_jobOption_file_data09_event.sh
        cd ../../dat/run/jpsi_inclusive/job_text/data09_event
        chmod 755 jobOptions_data09_event-*
        mv jobOptions_data09_event-388.sh jobOptions_data09_event-0.sh
        cd $HOME/bes/hypermiss
	   ;;

    0.1.10) echo "Submit Condor jobs on data 2009 event...2"
        cd dat/run/jpsi_inclusive/job_text/data09_event
        hep_sub -g physics -n 388 jobOptions_data09_event-%{ProcId}.sh
        cd $HOME/bes/hypermiss
        ;;

    0.1.11) echo "Check Condor jobs on data 2009 event..."
	   ./python/chk_condorjobs.py dat/run/jpsi_inclusive/event_data09 388
	   ;;

    0.1.12) echo  "Merge rootfile on data 2009 event..."
       ./python/mrg_rootfiles.py dat/run/jpsi_inclusive/event_data09 dat/run/jpsi_inclusive/merge_root_event09
        ;;

    0.1.13) echo "Generate plot for mgamgam "
        cd plots
        root -l plot_data_pi0.c
    	;;

    # --------------------------------------------------------------------------
    #  0.2 inclusiveMC  09
    # --------------------------------------------------------------------------


0.2) echo "[Running on inclusiveMC_09  data--HyperonDT]"
         ;;

    0.2.1) echo "Split MC sample with each group 20G ..."
	   ./python/get_samples.py /besfs2/offline/data/664-1/jpsi/09mc/dst dat/run/samples/inclusiveMC_09/mc_664p01_jpsi_09mc.txt 20G
	   # made 185 groups 
	   ;;

    0.2.2) echo "Generate Condor jobs on incl MC ---- 1..."
	    cd /besfs/users/amitraahul/bes/hypermiss/scripts/gen_script
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/gen_script/make_jobOption_file_inclusiveMC.sh ./
		cd $HOME/bes/hypermiss
        cd scripts/gen_script
        ./make_jobOption_file_inclusiveMC.sh
		cd ../../dat/run/jpsi_inclusive/job_text/inclusiveMC_09
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
            cd dat/run/jpsi_inclusive/job_text/inclusiveMC_09
            boss.exe jobOptions_inclusive_jpsi_mc-0.txt
            cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change test number."
        fi
        ;;

    0.2.4) echo "Submit Condor jobs on incl MC for 10 jobs---- 2..."
        cd dat/run/jpsi_inclusive/job_text/inclusiveMC_09
        boss.condor -g physics -n 10 jobOptions_inclusive_jpsi_mc-%{ProcId}.txt
        cd $HOME/bes/hypermiss	    
        ;;

    0.2.5) echo "Check condor jobs on inclusive MC..."
        ./python/chk_condorjobs.py dat/run/jpsi_inclusive/rootfile_inclusiveMC_09 10
        ;;

    0.2.6) echo "Submit Condor jobs on incl MC for all jobs---- 3..."
        cd dat/run/jpsi_inclusive/job_text/inclusiveMC_09
        boss.condor -g physics -n 185 jobOptions_inclusive_jpsi_mc-%{ProcId}.txt
        cd $HOME/bes/hypermiss	    
        ;;
        
    0.2.7) echo "Check condor jobs on inclusive MC ..."
        ./python/chk_condorjobs.py dat/run/jpsi_inclusive/rootfile_inclusiveMC_09 185
        ;;

    0.2.8) echo "Test 1 job on inclusive MC event..."
        ./python/sel_events.py dat/run/jpsi_inclusive/rootfile_inclusiveMC_09/jpsi_inclusive_jpsi_mc-1.root dat/run/jpsi_inclusive/event_inclusiveMC_09/jpsi_inclusiveMC_event-1.root                                                              
	   ;;

    0.2.9) echo "Generate Condor jobs on inclusive MC event ---- 1..."
        mkdir -p dat/run/jpsi_inclusive/job_text/inclusiveMC_event
        cd scripts/gen_script
        ./make_jobOption_file_inclusiveMC_event.sh
        cd ../../dat/run/jpsi_inclusive/job_text/inclusiveMC_event
        chmod 755 jobOptions_inclusive_mc_event-*
        mv jobOptions_inclusive_mc_event-185.sh jobOptions_inclusive_mc_event-0.sh
        cd $HOME/bes/hypermiss
	   ;;

    0.2.10) echo "Submit Condor jobs on inclusive MC event...2"
        cd dat/run/jpsi_inclusive/job_text/inclusiveMC_event
        hep_sub -g physics -n 185 jobOptions_inclusive_mc_event-%{ProcId}.sh
        cd $HOME/bes/hypermiss
        ;;

    0.2.11) echo "Check Condor jobs on inclusive MC event..."
	   ./python/chk_condorjobs.py dat/run/jpsi_inclusive/event_inclusiveMC_09 185
	   ;;

    0.2.12) echo  "Merge rootfile on inclusive MC event..."
       ./python/mrg_rootfiles.py dat/run/jpsi_inclusive/event_inclusiveMC_09 dat/run/jpsi_inclusive/merge_root_event09
        ;;

    0.2.13) echo "Generate plot for mgamgam "
        cd plots
        root -l plot_incl_pi0.c
    	;;

    # --------------------------------------------------------------------------
    #  0.3 signal MC  
    # --------------------------------------------------------------------------


0.3) echo "[run on signal MC--Xi0]"
	 ;;


    0.3.1) echo "simulation --10 signal MC sample interactively for Xi0 events..."
        echo "have you changed event number for 10 events to run interactively?(yes / NO)"
        echo "copy the decay file into besfs before running this option for a new decay mode"
        
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"

            cd /besfs/users/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts
            cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts/jobOptions_sim_jpsi2xi0.txt ./
            boss.exe jobOptions_sim_jpsi2xi0.txt
            cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change event number."
        fi
        ;;

    0.3.2) echo "submitting the condor job for simulation -- 20000 signal MC sample jpsi2xi0 events..."
        echo "have you checked the lxslc7 machine? Condor job is only applicable on lxslc7 machine.(yes / NO)"
        
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"
        
            cd /besfs/users/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts
            cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts/jobOptions_sim_jpsi2xi0.txt ./
            boss.condor -os SL6 jobOptions_sim_jpsi2xi0.txt
            cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO'."
        fi
        ;;

    0.3.3) echo "reconstruction -- generate 20000 signal MC sample..."
            
	    cd /besfs/users/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts/jobOptions_rec_jpsi2xi0.txt ./
        boss.condor -os SL6 jobOptions_rec_jpsi2xi0.txt
        cd $HOME/bes/hypermiss
        ;;

    0.3.4) echo "Preselection for 10 events -- generate root file [Checking interactively]..."

        echo "have you changed event number to 10 for interactive job?(yes / NO)"
        
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"
        
        cd /besfs/users/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts/jobOptions_jpsi2xi0_gen_mc.txt ./
	    boss.exe jobOptions_jpsi2xi0_gen_mc.txt
        cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change the event number"
        fi
        ;;


    0.3.5) echo "Preselection for 20k events -- generate root file [cluster job]..."
	
        echo "have you changed event number from 10 which was previously set for interactive job?(yes / NO)"
        
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"

	    cd /besfs/users/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts
        cp /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/scripts/xi0/jobs_scripts/jobOptions_jpsi2xi0_gen_mc.txt ./
	    boss.condor -g physics jobOptions_jpsi2xi0_gen_mc.txt
        cd $HOME/bes/hypermiss
        else
            echo "Default value is 'NO', please change the event number"
        fi
        ;;

    0.3.6) echo "Select events on signal MC sample..."
    #   ./python/sel_events.py dat/run/signalMC/root_jpsi2xi0/jpsi2xi0.root dat/run/signalMC/event_signalMC/jpsi2xi0_event_mostenergetic.root 
        ./python/sel_events.py dat/run/signalMC/root_jpsi2xi0/jpsi2xi0.root dat/run/signalMC/event_signalMC/jpsi2xi0_event.root 
	   ;;


    0.3.7) echo "Generate plot for mgamgam "
        cd plots
        root -l plot_pi0.c
    	;;
esac
