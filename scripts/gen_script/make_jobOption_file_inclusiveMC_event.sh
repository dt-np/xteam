#!/bin/bash

JobText_SaveDir=../../dat/run/jpsi_inclusive/job_text/inclusiveMC_event

for num in {1..185}
do
    jobOptions=jobOptions_inclusive_mc_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/hypermiss                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py dat/run/jpsi_inclusive/rootfile_inclusiveMC_09/jpsi_inclusive_jpsi_mc-${num}.root dat/run/jpsi_inclusive/event_inclusiveMC_09/jpsi_inclusiveMC_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done
