echo "Initializing...\n"
cd or-tools

make run SOURCE=../src/main.cc

cd ..
echo "\nSuccessfully initialized!\n"

echo "Running with user input...\n"
sh build.sh