./build.sh
if [ $? -eq 0 ]; then
    echo "-------------------"
    echo ""
    ./build/evently
else
    echo "Compilation failed"
    exit 1
fi