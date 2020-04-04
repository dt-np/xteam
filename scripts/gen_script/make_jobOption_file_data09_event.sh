#!/bin/bash

JobText_SaveDir=../../dat/run/jpsi_inclusive/job_text/data09_event


for num in {1..388}
do
    jobOptions=jobOptions_data09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/hypermiss                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py dat/run/jpsi_inclusive/rootfile_data09/jpsi_data09-${num}.root dat/run/jpsi_inclusive/event_data09/jpsi_data09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

