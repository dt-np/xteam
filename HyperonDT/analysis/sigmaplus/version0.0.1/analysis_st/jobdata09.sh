#!/bin/tcsh
cd /besfs/users/amitraahul/bes/hypermiss/dat/run/jpsi_inclusive/rootfile_data09
root -b <<EOF
.L ../STsigmaplus.cxx++
STsigmaplus("09datalist","jpsi_data09.root",false)
EOF
