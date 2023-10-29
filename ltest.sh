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

# test normal path, empty path, unset path
IS_PATH=1
if [ $IS_PATH -eq 1 ]
    then
        echo -en "\n#######################################\n"
        echo "./pipex mytest.sh wc path/test_cmd outfile"
        ./pipex mytest.sh wc path/test_cmd outfile
        echo "./pipex : $?"
        < mytest.sh wc | path/test_cmd > original
        echo "original: $?"

        echo
        echo "./pipex mytest.sh wc path/test_cmd2 outfile"
        ./pipex mytest.sh wc path/test_cmd2 outfile 
        echo "./pipex : $?"
        < mytest.sh wc | path/test_cmd2 > original
        echo "original: $?"

        echo
        echo "./pipex mytest.sh wc test_cmd outfile"
        ./pipex "mytest.sh" wc test_cmd outfile 
        echo "./pipex : $?"
        < mytest.sh wc | test_cmd > original
        echo "original: $?"

        echo
        echo "./pipex mytest.sh no_read no_exe outfile"
        ./pipex mytest.sh no_read no_exe outfile 
        echo "./pipex : $?"
        < mytest.sh no_read | no_exe > original
        echo "original: $?"

        touch inaccess
        chmod 000 inaccess
        echo
        ./pipex inaccess no_read no_exe inaccess 
        echo "./pipex : $?"
        < inaccess no_read | no_exe > inaccess
        echo "./pipex : $?"
fi