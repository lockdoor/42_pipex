#! /bin/bash

# cat << EOF > infile
# one two three four five
# six seven eight nine ten
# EOF
./pipex infile "grep six" "wc -w" outfile
# < infile grep "six" | wc -w
echo "exit code: "$?
# rm -f infile

# < infile grep "three" | awk '{print $3}'