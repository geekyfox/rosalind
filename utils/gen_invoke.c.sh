#!/bin/bash

for problem in $(ls src | egrep "([0-9]+)\-.*\.c" \
                        | sort \
                        | sed -e 's/[0-9\-]//g' -e 's/\.c//g')
do
    FUNS="$FUNS $problem/${problem}_solve"
done

echo "#include <stdbool.h>"
echo "#include <stdlib.h>"
echo "#include <string.h>"
echo
echo "#include \"../src/rosalind.h\""
echo
echo "void invoke(const char* key, FILE* in, FILE* out)"
echo "{"
    
for pair in $FUNS
do
    problem=$(echo $pair | awk -F '/' '{print $1}')
    fun=$(echo $pair | awk -F '/' '{print $2}')
    echo -e "\tif(strcmp(key, \"$problem\") == 0) {"
    echo -e "\t\t$fun(in, out);"
    echo -e "\t\treturn;"
    echo -e "\t}"
done

echo -e "\tfprintf(stderr, \"No solver for problem %s\\\n\", key);"
echo -e "\texit(1);"
echo "}"
echo

echo "bool has_solver(const char* key)"
echo "{"

for pair in $FUNS
do
    problem=$(echo $pair | awk -F '/' '{print $1}')
    fun=$(echo $pair | awk -F '/' '{print $2}')
    echo -e "\tif(strcmp(key, \"$problem\") == 0) {"
    echo -e "\t\treturn true;"
    echo -e "\t}"
done

echo -e "\tfprintf(stderr, \"No solver for problem %s\\\n\", key);"
echo -e "\treturn false;"
echo "}"
echo
