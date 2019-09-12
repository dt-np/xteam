#!/usr/bin/env python
"""
Check Condor jobs 
"""

__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__created__ = "[2017-10-24 Tue 10:21]" 

import sys
import os
from hurry.filesize import size 
from tools import BossLogFile, EventsLogFile 


def usage():
    sys.stdout.write('''
NAME
    chk_condorjobs.py 

SYNOPSIS

    ./chk_condorjobs.py  input_dir num_of_files

\n''')

    
def main():
    args = sys.argv[1:]
    if len(args) < 2:
        return usage()
    
    src = args[0]
    num = int(args[1])
    jobs_created = set(range(1, num+1))

    log = src
    logdir = src.split('/')[-1]
    
    if logdir in ['event_data_by_5', 'event_data09', 'event_data3650', 'event_data', 
    'event_inclusiveMC', 'rootfile_data09', 'rootfile_data_by_5', 'rootfile_data', 'rootfile_data3650', 
    'rootfile_inclusiveMC', 'event', 'Data12_event', 'rootfile','Data12', 'data', 'mc_psip12', 
    'con3650', 'data09', 'mc_psip09', 'inclusiveMC']:
        logfiletype = 'BossLogFile'
    elif logdir == 'events':
        logfiletype = 'EventsLogFile'
    else:
        raise NameError(logdir)

    if logdir in ['inclusiveMC']:
        # print(log)
        # print(logdir)
        #exit()
        pass
    else: 
        log = log.replace(logdir, 'log/%s' %logdir)
    
    sys.stdout.write('Scanning %s...\n' %src)

    file_list = []
    total_size = 0

    for root, dirs, files in os.walk(src):
        for f in files:
            file_list.append(int(f.split('-')[-1].split('.')[0]))
            total_size = total_size + os.path.getsize(os.path.join(root,f))

    sys.stdout.write('Checking log files...\n')
    jobs_not_terminated = []
    num_logfiles = []
    for root, dirs, files in os.walk(log):
        num_logfiles = files 
        if len(files) == 0:
            sys.stdout.write('No log files found!\n')
            break 
        for f in files:
            if logfiletype == 'BossLogFile': 
                l = BossLogFile( os.path.join(root, f) )
            elif logfiletype == 'EventsLogFile':
                l = EventsLogFile( os.path.join(root, f) )
            else:
                raise NameError(logfiletype) 

            if not l.terminated:
                sys.stdout.write('%s ... Not OK.\n' %f)
                job = f.split('-')[-1]
                jobs_not_terminated.append(job)
            else:
                sys.stdout.write('%s ... OK.\n' %f)


    sys.stdout.write('\nFound %s files, with total size %s.\n' %(
        len(file_list), size(total_size)))
    
    if len(jobs_not_terminated) > 0: 
        sys.stdout.write('Non-terminated jobs are (%s): %s\n' % (
            len(jobs_not_terminated), ','.join(jobs_not_terminated)))
    elif len(num_logfiles) > 0 :
        sys.stdout.write('All finished jobs are terminated correctly. \n')

    if len(file_list) < num:
        jobs_missing = jobs_created.difference(file_list)
        jobs_missing = [str(li) for li in jobs_missing]
        sys.stdout.write('Missing jobs are (%s): %s\n' % (
            len(jobs_missing), ','.join(jobs_missing)))
    else:
        sys.stdout.write('No missing jobs.\n')
        
                
if __name__ == '__main__':
    main()
