# romp
a build system
## build
```sh
gcc -shared fs.c -o libfs.so
gcc fs.c m_fs.c -shared -fpic -I/usr/local/include -L/usr/local/lib -llua -o fsx.so
gcc -shared -Wall -Wextra -pedantic -O3 -g -lluajit  -pagezero_size 10000 -image_base 100000000 src/*.c -o src/fsx.so
```
