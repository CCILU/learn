gcc -fPIC -shared -g -o liblist.so *.c
cp ./liblist.so /lib/ -rf
cp ./liblist.so /lib64/ -rf