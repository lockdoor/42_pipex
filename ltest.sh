#! /bin/bash

# ./pipex mytest.sh cat wx outfile
# valgrind --leak-check=full -s ./pipex mytest.sh cat wx outfile
# /usr/local/bin/valgrind --leak-check=full -s ./pipex mytest.sh cat wx outfile


# wx: No such file or directory
# ./pipex mytest.sh /bin/cat wx outfile
# < mytest.sh /bin/cat | wx > original

# add path
# PATH="$(pwd)/path:$PATH"
# ./pipex mytest.sh cat wx outfile
# < mytest.sh cat | wx > original

# ./pipex mytest cat wx outfile
# < mytest cat | wx > original

# when find command take these error
# command not found => argument have no path it find path by env
# no such file => 
## argument have path eg "not_exit/"
## path is empty
# permission denied
# echo
# ./pipex "mytest.sh" wc test_cmd outfile
# echo "./pipex : $?"
# < "mytest.sh" wc | test_cmd > original 
# echo "original: $?"
# PATH="$(pwd):$PATH"
# test normal path, empty path, unset path
NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

IS_PATH=1
WAIT_TIME=4;

function check_diff {
    printf "${RED}"
    /usr/bin/diff original outfile
    printf "${NC}"
}

if [ $IS_PATH -eq 1 ]
    then
        # PATH="$(pwd):$PATH"

        # echo -en "\n#######################################\n"
        # echo "./pipex mytest.sh wc test_cmd outfile"
        # ./pipex mytest.sh wc test_cmd outfile
        # echo "./pipex : $?"
        # < mytest.sh wc | test_cmd > original
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # echo
        # echo "./pipex mytest.sh wc test_cmd2 outfile"
        # ./pipex mytest.sh wc test_cmd2 outfile 
        # echo "./pipex : $?"
        # < mytest.sh wc | test_cmd2 > original
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # echo
        # echo "./pipex mytest.sh wc test_cmd outfile"
        # ./pipex "mytest.sh" wc test_cmd outfile 
        # echo "./pipex : $?"
        # < mytest.sh wc | test_cmd > original
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # echo
        # echo "./pipex mytest.sh no_read no_exe outfile"
        # ./pipex mytest.sh no_read no_exe outfile 
        # echo "./pipex : $?"
        # < mytest.sh no_read | no_exe > original
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # touch inaccess
        # chmod 000 inaccess
        # echo
        # ./pipex inaccess no_read no_exe inaccess 
        # echo "./pipex : $?"
        # < inaccess no_read | no_exe > inaccess
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # echo
        # echo "./pipex mytest.sh ./wc ./test_cmdq outfile"
        # ./pipex mytest.sh ./wc ./test_cmdq outfile
        # echo "./pipex : $?"
        # < mytest.sh ./wc | ./test_cmdq > original
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # echo
        # echo "./pipex mytest.sh ./wc ./test_cmdq outfile"
        # ./pipex mytest.sh ./wc ./test_cmdq outfile
        # echo "./pipex : $?"
        # < mytest.sh ./wc | ./test_cmdq > original
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # echo
        # echo "./pipex mytest.sh ./wc ./wc outfile"
        # ./pipex mytest.sh ./wc ./wc outfile
        # echo "./pipex : $?"
        # < mytest.sh ./wc | ./wc > original
        # echo "original: $?"
        # check_diff
        # sleep $WAIT_TIME

        # in this case has error differrent 
        # but type command in terminal it is't fail
        echo
        echo "./pipex mytest.sh ./wc wc outfile"
        ./pipex mytest.sh ./wc wc outfile
        echo "./pipex : $?"
        < mytest.sh ./wc | wc > original
        echo "original: $?"
        check_diff
        sleep $WAIT_TIME

        echo
        echo "./pipex mytest.sh wc wc outfile"
        ./pipex mytest.sh wc wc outfile
        echo "./pipex : $?"
        < mytest.sh wc | wc > original
        echo "original: $?"
        check_diff
        sleep $WAIT_TIME
fi