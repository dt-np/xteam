#!/usr/bin/env python
"""
Merge root files
"""

__author__ = "SHI Xin <shixin@ihep.ac.cn>"
__copyright__ = "Copyright (c) SHI Xin"
__created__ = "[2016-06-20 Mon 09:46]" 

import sys
import os
from tools import check_and_join, group_files_by_size, proc_cmd
from hurry.filesize import size 

def usage():
    sys.stdout.write('''
NAME
    mrg_rootfiles.py 

SYNOPSIS

    ./mrg_rootfiles.py  inputdir outputdir 

AUTHOR 
    SHI Xin <shixin@ihep.ac.cn> 

DATE
    July 2016 
\n''')

    
def main():
    args = sys.argv[1:]
    if len(args) < 2:
        return usage()
    
    src = args[0]
    dst = args[1]
    sys.stdout.write('Merging %s...\n' %src)

    print src, dst
    merge_root_files(src, dst)
    

def merge_root_files(srcdir, dstdir, size_max='2G', nfile_max=500):
    file_list = []
    size_list = []
    for root, dirs, files in os.walk(srcdir):
        for f in files:
            s = os.path.getsize(os.path.join(root, f))
            file_list.append(os.path.join(root, f))
            size_list.append(s)
            
    totalsize = sum(size_list)
    sys.stdout.write('total of %s files, size %s.\n' % (len(file_list), size(totalsize)))

    com_name = file_list[0].split('-')[0].split('/')[-1]
    groups = group_files_by_size(file_list, size_max)
    ngroups = len(groups) 

    for i in range(ngroups):
        print i
        sourcefiles = ' '.join(groups[i-1])
        targetname = '%s_merged_%s.root' % (com_name, i+ngroups)
        targetfile = check_and_join(dstdir, targetname)
        cmd = 'hadd %s %s' %(targetfile, sourcefiles)
        sys.stdout.write('merging %s of %s ...\n' %(i+1, ngroups))
        sys.stdout.flush()
        output = proc_cmd(cmd)
        print output

if __name__ == '__main__':
    main()
