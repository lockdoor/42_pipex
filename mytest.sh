#! /bin/bash

# init infile
< mytest.sh cat > infile
clear

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

TEST_ACCESS=1
TEST_ACCESS_COMMAND=0
TEST_MANDATORY=0
TEST_INVALID_ARG=0
TEST_INVALID_ARG_HEREDOC=0
TEST_AWK=0
TIME1=2

function clear_screen {
    sleep 5
    clear
}

function check_diff {
    printf "${RED}"
    diff original outfile
    printf "${NC}"
}

function check_exit_code {
	if [ $1 -eq $2 ]
		then
			printf "${ULINE}${GREEN}My program exit code: $1 == OK${NC}\n"
		else
			printf "${ULINE}${RED}My program exit code: $1 == KO${NC}\n"
	fi
}

# -----------------------------------------
#             MANDATORY ZONE
# -----------------------------------------
if [ $TEST_MANDATORY -eq 1 ]
	then
		echo "normal case"
		printf "${MAGENTA}./pipex \"infile\" \"cat\" \"hostname\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "infile" "cat" "hostname" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | hostname > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "normal case"
		printf "${MAGENTA}./pipex \"infile\" \"grep Now\" \"head -2\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "infile" "grep Now" "head -2" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile grep Now | head -2 > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error infile"
		printf "${MAGENTA}./pipex \"not-existing/infile\" \"grep Now\" \"wc -w\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "not-existing/infile" "grep Now" "wc -w" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< not-existing/infile grep Now | wc -w > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error command 2"
		printf "${MAGENTA}./pipex \"infile\" \"cat\" \"notexisting\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "infile" "cat" "notexisting" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | notexisting > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "normal case"
		printf "${MAGENTA}./pipex \"/infile1\" \"ls\" \"wc\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "/infile" "ls" "wc" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< /infile1 ls | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error infile"
		printf "${MAGENTA}./pipex \"non_exist_input\" \"ls\" \"wc\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "non_exist_input" "ls" "wc" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< non_exist_input ls | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error outfile"
		printf "${MAGENTA}./pipex \"infile\" \"ls\" \"wc\" \"non_exist_output/file\"\n${NC}"
		valgrind --leak-check=full ./pipex "infile" "ls" "wc" "non_exist_output/file"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile ls | wc > non_exist_output/file
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error infile cmd1 cmd2"
		printf "${MAGENTA}./pipex \"non_exist_input\" \"/bin/catsdc\" \"wcss\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "non_exist_input" "/bin/catsdc" "wcss -cl" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< non_exist_input /bin/catsdc | wcss -cl > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error cmd1 cmd2"
		printf "${MAGENTA}./pipex \"infile\" \"/bin/caqwdt\" \"/bin/lsqwd -ls\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "infile" "/bin/caqwdt" "/bin/lsqwd -ls" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile /bin/caqwdt  | /bin/lsqwd -ls > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error infile cmd1 cmd2 "
		printf "${MAGENTA}./pipex \"non_exist_input\" \"/bin/caqwdt\" \"/bin/lsqwd -ls\" \"outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "non_exist_input" "/bin/caqwdt" "/bin/lsqwd -ls" "outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile /bin/caqwdt  | /bin/lsqwd -ls > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen

		echo "error cmd1 cmd2 outfile"
		printf "${MAGENTA}./pipex \"infile\" \"/bin/caqwdt\" \"/bin/lsqwd -ls\" \"nodir/outfile\"\n${NC}"
		valgrind --leak-check=full ./pipex "infile" "/bin/caqwdt" "/bin/lsqwd -ls" "nodir/outfile"
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile /bin/caqwdt | /bin/lsqwd -ls > nodir/original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		clear_screen
fi

# -----------------------------------------

# -------------------------------------------
# test number of argument
# -------------------------------------------
if [ $TEST_INVALID_ARG -eq 1 ]
	then
		echo "wrong argument expect Ivalid argument, exit code 1"
		printf "\n${MAGENTA}./pipex\n${NC}"
		./pipex
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex infile\n${NC}"
		./pipex infile
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex infile cat\n${NC}"
		./pipex infile cat
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex infile cat wc\n${NC}"
		./pipex infile cat wc
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex infile cat wc outfile\n${NC}"
		./pipex infile cat wc outfile
		check_exit_code $? 0
		sleep $TIME1
fi

if [ $TEST_INVALID_ARG_HEREDOC -eq 1 ]
	then
		printf "\n${MAGENTA}here_doc wrong argument expect Ivalid argument, exit code 1\n${NC}"
		printf "\n${MAGENTA}./pipex\n${NC}"
		./pipex
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex here_doc\n${NC}"
		./pipex here_doc
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex here_doc limit\n${NC}"
		./pipex here_doc limit
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex here_doc limit cat\n${NC}"
		./pipex here_doc limit cat
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex here_doc limit cat wc\n${NC}"
		./pipex here_doc limit cat wc
		check_exit_code $? 1
		sleep $TIME1

		printf "\n${MAGENTA}./pipex here_doc limit cat wc outfile\n${NC}"
		echo -en "lsdjf sdkfjalf\nlimit\n" > .tempfile
		< .tempfile ./pipex here_doc limit cat wc outfile
		check_exit_code $? 0
		rm -f .tempfile
		sleep $TIME1
fi

# -------------------------------------------
# test access infile outfile
# 444 = r, 222 = w, 111 = x
# -------------------------------------------
if [ $TEST_ACCESS -eq 1 ]
	then
		rm -f inaccess outfile original

		echo "#################################################"
		printf "${MAGENTA}\nno infile\n${NC}"
		./pipex inaccess cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< inaccess cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		touch inaccess

		printf "${MAGENTA}\ninfile 000 = zero bit${NC}\n"
		chmod 000 inaccess
		./pipex inaccess cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< inaccess cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		printf "${MAGENTA}\ninfile 111 = execute only${NC}\n"
		chmod 111 inaccess
		./pipex inaccess cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< inaccess cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		printf "${MAGENTA}\ninfile 222 = write only${NC}\n"
		chmod 222 inaccess
		./pipex inaccess cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< inaccess cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		printf "${MAGENTA}\ninfile 444 = read only${NC}\n"
		chmod 444 inaccess
		./pipex inaccess cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< inaccess cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		rm -f inaccess

		printf "${MAGENTA}\noutfile 000 = zero bit${NC}\n"
		chmod 000 outfile original
		./pipex infile cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		sleep $TIME1

		printf "${MAGENTA}\noutfile 111 = execute only${NC}\n"
		chmod 111 outfile original
		./pipex infile cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		sleep $TIME1

		printf "${MAGENTA}\noutfile 444 = read only${NC}\n"
		chmod 444 outfile original
		./pipex infile cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		sleep $TIME1

		printf "${MAGENTA}\noutfile 222 = write only${NC}\n"
		chmod 222 outfile original
		./pipex infile cat wc outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | wc > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		sleep $TIME1

		rm -f outfile original
		# clear_screen
fi

# -------------------------------------------
# test access command
# 444 = r, 222 = w, 111 = x
# -------------------------------------------
if [ $TEST_ACCESS_COMMAND -eq 1 ]
	then
		rm -f outfile original
		touch test_cmd

		chmod 000 test_cmd
		printf "${MAGENTA}\ntest_cmd 000 = zero bit${NC}\n"
		printf "${MAGENTA}\n./pipex infile cat ./test_cmd outfile\n${NC}"
		./pipex infile cat ./test_cmd outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | ./test_cmd > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		chmod 222 test_cmd
		printf "${MAGENTA}\ntest_cmd 222 = write only${NC}\n"
		printf "${MAGENTA}\n./pipex infile cat ./test_cmd outfile\n${NC}"
		./pipex infile cat ./test_cmd outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | ./test_cmd > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		chmod 444 test_cmd
		printf "${MAGENTA}\ntest_cmd 444 = read only${NC}\n"
		printf "${MAGENTA}\n./pipex infile cat ./test_cmd outfile\n${NC}"
		./pipex infile cat ./test_cmd outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | ./test_cmd > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		chmod 111 test_cmd
		printf "${MAGENTA}\ntest_cmd 111 = fake execute${NC}\n"
		printf "${MAGENTA}\n./pipex infile cat ./test_cmd outfile\n${NC}"
		./pipex infile cat ./test_cmd outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | ./test_cmd > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		chmod 777 test_cmd
		printf "${MAGENTA}\ntest_cmd 777 = full access${NC}\n"
		printf "${MAGENTA}\n./pipex infile cat ./test_cmd outfile\n${NC}"
		./pipex infile cat ./test_cmd outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | ./test_cmd > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		rm -f test_cmd

		printf "${MAGENTA}\n./pipex infile cat /test_cmd outfile\n${NC}"
		./pipex infile cat /test_cmd outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | /test_cmd > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		printf "${MAGENTA}\n./pipex infile cat test/test_cmd outfile\n${NC}"
		./pipex infile cat test/test_cmd outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile cat | test/test_cmd > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1
		clear_screen
fi

# check_diff
# clear_screen

# -------------------------------------------
# spacial test for awk
# -------------------------------------------

if [ $TEST_AWK -eq 1 ]
	then
		rm -f outfile original
		cat mytest.sh > infile

		./pipex infile "head -n1" "awk '{print \$1}'" outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile head -n1 | awk '{print $1}' > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		./pipex infile "head -n1" "awk \"{print \$1}\"" outfile
		printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
		< infile head -n1 | awk '{print $1}' > original
		# < infile head -n1 | awk "{print $1}" > original
		printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
		check_diff
		sleep $TIME1

		# clear_screen
fi

# when wrong path should print "no such file"

# -----------------------------------------


# -----------------------------------------
#               BONUS ZONE
# -----------------------------------------
# echo "error multi wrong cmd outfile"
# printf "${MAGENTA}./pipex \"infile\" \"/bin/caqwdt\" "wc" "wc" "wsdfca" \"/bin/lsqwd -ls\" \"nodir/outfile\"\n${NC}"
# valgrind --leak-check=full ./pipex "infile" "/bin/caqwdt" "cat" "wc" "wc" "wsdfca" "/bin/lsqwd -ls" "nodir/outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile /bin/caqwdt | cat | wc | wc | wsdfca | /bin/lsqwd -ls > nodir/outfile
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff
# clear_screen

# here_doc
# echo
# printf "${MAGENTA}here_doc with no limiter\nexpect: error${NC}\n"
# echo -en "i am here_doc\n" > here_doc
# valgrind --leak-check=full < here_doc ./pipex "here_doc" "EOF"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# rm -f here_doc
# clear_screen

# ===============================

# echo
# printf "${MAGENTA}here_doc with wrong limiter 1\nexpect: error${NC}\n"
# echo -en "i am here_doc\nEOF" > here_doc
# < here_doc ./pipex "here_doc" "EOF"
# rm -f here_doc

# echo
# printf "${MAGENTA}here_doc with wrong limiter 2\nexpect: error${NC}\n"
# echo -en "i am here_doc\nEOFq\n" > here_doc
# < here_doc ./pipex "here_doc" "EOF"
# rm -f here_doc

# echo
# printf "${MAGENTA}here_doc with wrong limiter 3\nexpect: error${NC}\n"
# echo -en "i am here_doc\nEO\n" > here_doc
# < here_doc ./pipex "here_doc" "EOF"
# rm -f here_doc

# echo
# printf "${MAGENTA}here_doc with correct limiter\nexpect: ok${NC}\n"
# echo -en "i am here_doc\nEOF\n" > here_doc
# < here_doc ./pipex "here_doc" "EOF"
# rm -f here_doc

# rm -f outfile
# rm -f original
# # echo
# echo -en "i am here_doc\nEOF\n" > here_doc
# echo -en "i am here_doc\n" > infile1
# echo -e "sgfefeqd qwdqwdddafasd s+64 65 30 9 2 92 ad asd lim asd as d asd\n asdasd \nlim\n a dasd sd \n asdasd asdasdsbvfsbvsdd asd asd\n afdsvdsvasdqpkqwd ew edfsb" > in_file2
# < here_doc ./pipex "here_doc" "EOF" "cat" "wc -cl" "grep 0" "sort" "cat" "outfile"
# < infile1 cat | wc -cl |  grep 0  | sort | cat > original

# < here_doc ./pipex "here_doc" "EOF" "cat" "wc -cl" "cat" "outfile"
# ./pipex "here_doc" "EOF" "cat" "wc -cl" "grep 0" "sort" "cat" "outfile"

# ./pipex "here_doc" "EOF" "cat" "cat" "cat" "cat" "wc" "outfile"
# valgrind < in_file2 ./pipex "here_doc" "lim2" "cat" "cat" "cat" "cat" "wc" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"

# < infile1 cat | cat | cat | cat | wc > original
# << lim2 < infile_2 cat | cat | cat | cat | wc > original
# i am here_doc
# # lim2
# # < infile1 cat | wc -cl | sort | cat > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff
# rm -f here_doc
rm -f infile


