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
# printf "${MAGENTA}./pipex \"infile\" \"ls\" \"wc\" \"non_exist_input/file\"\n${NC}"
# ./pipex "infile" "ls" "wc" "non_exist_input/file"
# printf "${ULINE}${GREEN}My program exit code: $?\n${NC}"
# < infile ls | wc > non_exist_input/file
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
# ./pipex "infile" "/bin/caqwdt" "/bin/lsqwd -ls" "outfile"
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

./pipex infile oeriurn ououfn outfile
