set -e
set -x

TRAVIS_ROOT="$1"

if [ ! -d "$TRAVIS_ROOT/fgmpi" ]; then

    cd $TRAVIS_ROOT

    # TAR build
    #wget --no-check-certificate -q http://www.cs.ubc.ca/~humaira/code/fgmpi-2.0.tar.gz
    #tar -C $TRAVIS_ROOT -xzf fgmpi-2.0.tar.gz
    #cd $TRAVIS_ROOT/fgmpi-2.0

    # GIT build
    git clone --depth 10 https://github.com/humairakamal/fgmpi.git fgmpi-source
    cd $TRAVIS_ROOT/fgmpi-source
    ./autogen.sh

    # TAR or GIT
    mkdir build && cd build
    # Clang defaults to C99, which chokes on "Set_PROC_NULL"
    # -Wno-macro-redefined silences numerous instances of the same warning.
    #../configure --disable-fortran --disable-romio CFLAGS="-std=gnu89 -Wno-macro-redefined" --prefix=$TRAVIS_ROOT/fgmpi
    ../configure FC=false --prefix=$TRAVIS_ROOT/fgmpi --disable-fortran --disable-fxx --disable-romio
    make
    make install

    # Package install
    # TODO (restore from older version but unpack in $TRAVIS_ROOT without sudo)

else
    echo "FG-MPI installed..."
    find $TRAVIS_ROOT/fgmpi -name mpiexec
    find $TRAVIS_ROOT/fgmpi -name mpicc
    mpicc -show
fi
