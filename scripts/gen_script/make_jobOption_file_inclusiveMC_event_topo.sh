#!/bin/bash

JobText_SaveDir=../../dat/run/jpsi_inclusive/job_text/inclusiveMC_event_topo

for num in {1..185}
do
    jobOptions=jobOptions_inclusive_mc_event_topo-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/hypermiss                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_top.py dat/run/jpsi_inclusive/rootfile_inclusiveMC_09/jpsi_inclusive_jpsi_mc-${num}.root dat/run/jpsi_inclusive/event_inclusiveMC_09_topo/jpsi_inclusiveMC_event_topo-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done
