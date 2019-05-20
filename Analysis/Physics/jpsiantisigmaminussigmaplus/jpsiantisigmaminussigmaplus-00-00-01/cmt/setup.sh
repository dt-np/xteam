# echo "Setting jpsiantisigmaminussigmaplus jpsiantisigmaminussigmaplus-00-00-01 in /afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/Analysis/Physics/jpsiantisigmaminussigmaplus/jpsiantisigmaminussigmaplus-00-00-01"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/ihep.ac.cn/bes3/offline/ExternalLib/contrib/CMT/v1r20p20081118; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=jpsiantisigmaminussigmaplus -version=jpsiantisigmaminussigmaplus-00-00-01 -path=/afs/ihep.ac.cn/users/a/amitraahul/bes/hypermiss/Analysis/Physics/jpsiantisigmaminussigmaplus/jpsiantisigmaminussigmaplus-00-00-01/cmt  -no_cleanup $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

