# Build your own cross compiler from scratch

This little guide is mostly a copy and paste from the [OSDev wiki page for building your own cross compiler](http://wiki.osdev.org/GCC_Cross-Compiler), but adapted for 42 school students (which I'll assume you're on).

## Before building anything

You need in your sgoinfre some place like the /usr/ directory and the bin directory of said /usr-like in your `$PATH`

## Gathering everything

The OSDev wiki will tell you to download some packages, as we don't have root access on 42 machines you will have to build everything manually.

Download every package (take the latest version) and extract them in a directory in your sgoinfre

| Package name | Description | Link |
|:-|:-|:-|
|Bison|Parser generator| [GNU Mirror](https://ftp.gnu.org/gnu/bison/) |
|Flex|[Lexer](https://en.wikipedia.org/wiki/Lexical_analysis)| [Github release](https://github.com/westes/flex/releases/) |
|GMP|Arithmetic library| [GNU Mirror](https://ftp.gnu.org/gnu/gmp/) |
|MPFR|Arithmetic library for floating numbers (based on GMP)| [GNU Mirror](https://ftp.gnu.org/gnu/mpfr/) |
|MPC|Arithmetic library for complex numbers (based on GMP)| [GNU Mirror](https://ftp.gnu.org/gnu/mpc/) |
|M4|Macro preprocessor| [GNU Mirror](https://ftp.gnu.org/gnu/m4/) |
|Texinfo|GNU's version of manpages| [GNU Mirror](https://ftp.gnu.org/gnu/texinfo/) |
|Binutils|Collection of tools such as AS, LD...| [GNU Mirror](https://sourceware.org/pub/binutils/releases/) **DON'T download the "with gold" package!** |
|GCC|Compiler| [GNU Mirror](https://ftp.gnu.org/gnu/gcc/) files are in directories, click on the latest version |
|GDB|Debugger (optional)| [GNU Mirror](https://ftp.gnu.org/gnu/gdb/) |

## Building everything

Now that you got all the packages you will need to build them

First let's set some environment variables

```bash
export PREFIX="<your sgoinfre directory or some place in your system if you have enough space>"
export TARGET=i686-elf # KFS is 32 bits
export PATH="$PATH:$PREFIX/bin"
```

Once all the variables are set you can build everything. Since some packages depends on others (ie. Bison depends on M4) we will build in the following order:
0. M4
1. Bison
2. Flex
3. GMP
4. MPFR
5. MPC
6. Texinfo
7. Binutils
8. GCC
9. GDB

### M4, Bison, Flex, Texinfo and GMP

Configure the makefile

```bash
./configure --prefix=<your "usr-like" directory>
```

Compile and install

```bash
make
make install
```

### MPFR, MPC

Configure the makefile

```bash
./configure --prefix=<your "usr-like" directory> --with-gmp=<your "usr-like" directory>/include
```

Compile and install

```bash
make
make install
```

### Binutils

Stay in the directory where all packages are and create a new one called `build-binutils` and `cd` into it

Configure the makefile

```bash
../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror --enable-default-execstack=no
```

Compile and install

```bash
make
make install
```

### GCC

Stay in the directory where all packages are and create a new one called `build-gcc` and `cd` into it

Configure the makefile

```bash
../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --enable-initfini-array --disable-hosted-libstdcxx --with-mpfr=<your "usr-like" directory>
```

Compile and install

```bash
make all-gcc
make all-target-libgcc
make all-target-libc++-v3
make install-gcc
make install-target-libgcc
make install-target-libc++-v3
```

## Testing and finishing

Congrats! You just compiled everything you will need for KFS!

Test if everything works well by calling GCC (from the absolute path).

If you get a message like this, you can add to your PATH the place where all the binaries you just compiled are installed in your shell config file.

```
i686-elf-gcc: fatal error: no input files
compilation terminated.
```

If not you must restart.
