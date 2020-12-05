echo "Initializing...\n"
cd or-tools_Ubuntu-20.04-64bit_v8.0.8283

make run SOURCE=../src/main.cc

cd ..
echo "\nSuccessfully initialized!\n"

echo "Running with user input...\n"
sh build.sh