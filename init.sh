echo "Initializing...\n"
cd or-tools

make run SOURCE=../src/main.cc

cd ..
echo "\nSuccessfully initialized!\n"

sh build.sh