echo "Running with user input...\n"
cd or-tools/bin

if ./main --file ../../user.csv; then
    mv out.csv ../../out.csv
fi