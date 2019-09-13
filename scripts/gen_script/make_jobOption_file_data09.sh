#!/bin/bash

JobText_SaveDir=../../dat/run/jpsi_inclusive/job_text/data

for num in {1..394}
do
    file_list=data_664p01_jpsi_20G-${num}.txt
    rootfile=jpsi_data09-${num}.root
    jobOptions=jobOptions_jpsi_09-${num}.txt
    echo   "#include \"\$ROOTIOROOT/share/jobOptions_ReadRec.txt\"        "  > ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$VERTEXFITROOT/share/jobOptions_VertexDbSvc.txt\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MAGNETICFIELDROOT/share/MagneticField.txt\"      " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ABSCORROOT/share/jobOptions_AbsCor.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$HOME/bes/hypermiss/dat/run/samples/data/$file_list\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.DLLs += {\"HyperonDecayAlg\"};                       " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.TopAlg += { \"HyperonDecayAlg\" };                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL ) " >> ${JobText_SaveDir}/${jobOptions}
    echo   "MessageSvc.OutputLevel = 5;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Number of events to be processed (default is 10)           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//ApplicationMgr.EvtMax = 5000;                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.EvtMax = -1;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.HistogramPersistency = \"ROOT\";               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "NTupleSvc.Output = {\"FILE1 DATAFILE='$HOME/bes/hypermiss/dat/run/jpsi_inclusive/rootfile_data09/$rootfile' OPT='NEW' TYP='ROOT'\"};" >> ${JobText_SaveDir}/${jobOptions}

    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
done
