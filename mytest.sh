#! /bin/bash

NC="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

# cat << EOF > infile
# one two three four five
# six seven eight nine ten
# EOF
# ./pipex infile "grep six" "wc -w" outfile
# < infile grep "six" | wc -w
# echo "exit code: "$?
# rm -f infile

# < infile grep "three" | awk '{print $3}'

function check_diff {
    printf "${RED}"
    diff original outfile
    printf "${NC}"
}

# echo
# printf "${MAGENTA}./pipex \"infile\" \"cat\" \"hostname\" \"outfile\"\n${NC}"
# ./pipex "infile" "cat" "hostname" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile cat | hostname > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"infile\" \"grep Now\" \"head -2\" \"outfile\"\n${NC}"
# ./pipex "infile" "grep Now" "head -2" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile grep Now | head -2 > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"not-existing/infile\" \"grep Now\" \"wc -w\" \"outfile\"\n${NC}"
# ./pipex "not-existing/infile" "grep Now" "wc -w" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < not-existing/infile grep Now | wc -w > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"infile\" \"cat\" \"notexisting\" \"outfile\"\n${NC}"
# ./pipex "infile" "cat" "notexisting" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile cat | notexisting > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"/infile1\" \"ls\" \"wc\" \"outfile\"\n${NC}"
# ./pipex "/infile" "ls" "wc" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < /infile1 ls | wc > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"non_exist_input\" \"ls\" \"wc\" \"outfile\"\n${NC}"
# ./pipex "non_exist_input" "ls" "wc" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < non_exist_input ls | wc > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"infile\" \"ls\" \"wc\" \"non_exist_output/file\"\n${NC}"
# ./pipex "infile" "ls" "wc" "non_exist_output/file"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile ls | wc > non_exist_output/file
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"non_exist_input\" \"/bin/catsdc\" \"wcss\" \"outfile\"\n${NC}"
# ./pipex "non_exist_input" "/bin/catsdc" "wcss -cl" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < non_exist_input /bin/catsdc | wcss -cl > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"infile\" \"/bin/caqwdt\" \"/bin/lsqwd -ls\" \"outfile\"\n${NC}"
# valgrind ./pipex "infile" "/bin/caqwdt" "/bin/lsqwd -ls" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile /bin/caqwdt  | /bin/lsqwd -ls > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"non_exist_input\" \"/bin/caqwdt\" \"/bin/lsqwd -ls\" \"outfile\"\n${NC}"
# ./pipex "non_exist_input" "/bin/caqwdt" "/bin/lsqwd -ls" "outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile /bin/caqwdt  | /bin/lsqwd -ls > original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# echo
# printf "${MAGENTA}./pipex \"infile\" \"/bin/caqwdt\" \"/bin/lsqwd -ls\" \"nodir/outfile\"\n${NC}"
# ./pipex "infile" "/bin/caqwdt" "/bin/lsqwd -ls" "nodir/outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile /bin/caqwdt | /bin/lsqwd -ls > nodir/original
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# < exist_input /bin/caqwdt | cat | wc | wc | wsdfca | /bin/lsqwd -ls > nodir/outfiile
# echo
# printf "${MAGENTA}./pipex \"exist_input\" \"/bin/caqwdt\" "wc" "wc" "wsdfca" \"/bin/lsqwd -ls\" \"nodir/outfile\"\n${NC}"
# ./pipex "exist_input" "/bin/caqwdt" "cat" "wc" "wc" "wsdfca" "/bin/lsqwd -ls" "nodir/outfile"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < exist_input /bin/caqwdt | cat | wc | wc | wsdfca | /bin/lsqwd -ls > nodir/outfiile
# printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
# check_diff

# here_doc
# echo
# printf "${MAGENTA}here_doc with no limiter\nexpect: error${NC}\n"
# echo -en "i am here_doc\n" > here_doc
# < here_doc ./pipex "here_doc" "EOF"
# rm -f here_doc

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

rm -f outfile
rm -f original
# echo
echo -en "i am here_doc\nEOF\n" > here_doc
echo -en "i am here_doc\n" > infile1
# < here_doc ./pipex "here_doc" "EOF" "cat" "wc -cl" "grep 0" "sort" "cat" "outfile"
# < infile1 cat | wc -cl |  grep 0  | sort | cat > original

# < here_doc ./pipex "here_doc" "EOF" "cat" "wc -cl" "cat" "outfile"
# ./pipex "here_doc" "EOF" "cat" "wc -cl" "grep 0" "sort" "cat" "outfile"

# ./pipex "here_doc" "EOF" "cat" "cat" "cat" "cat" "wc" "outfile"
< here_doc ./pipex "here_doc" "EOF1" "cat" "cat" "cat" "cat" "wc" "outfile"
printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"

# < infile1 cat | cat | cat | cat | wc > original
<< EOF1 cat | cat | cat | cat | wc > original
i am here_doc
EOF
# < infile1 cat | wc -cl | sort | cat > original
printf "${ULINE}${GREEN}Original exit code: $?\n${NC}"
check_diff
rm -f here_doc
rm -f infile1


