#! /bin/bash
# test execute shell script

echo "#################################"
echo "hostname" > bbbbssss
/bin/chmod +x bbbbssss
./pipex btest.sh ./bbbbssss cat outfile
echo "./pipex : $?"
< btest.sh ./bbbbssss | cat > original
echo "original: $?"
/usr/bin/diff original outfile

echo
./pipex btest.sh bbbbssss cat outfile
echo "./pipex : $?"
< btest.sh bbbbssss | cat > original
echo "original: $?"
/usr/bin/diff original outfile

echo
echo "hostname55" > bbbbssss
./pipex btest.sh ./bbbbssss cat outfile
echo "./pipex : $?"
< btest.sh ./bbbbssss | cat > original
echo "original: $?"
/usr/bin/diff original outfile

echo
/bin/chmod -x bbbbssss
./pipex btest.sh ./bbbbssss cat outfile
echo "./pipex : $?"
< btest.sh ./bbbbssss | cat > original
echo "original: $?"
/usr/bin/diff original outfile

bin/rm -f bbbbssss