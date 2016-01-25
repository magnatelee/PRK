set -e
set -x

TRAVIS_ROOT="$1"

if [ ! -d "$TRAVIS_ROOT/fgmpi" ]; then

    cd $TRAVIS_ROOT

    # For some reason, Git builds fail on Mac with the following errors,
    # so we will just try the tar release there.
    # configure.ac:6268: error: required file 'src/binding/fortran/use_mpi_f08/mpi_f08_compile_constants.f90.in' not found
    # configure.ac:6268: error: required file 'src/binding/fortran/use_mpi_f08/mpi_c_interface_types.f90.in' not found
    case "$TRAVIS_OS_NAME" in
        osx)
            wget --no-check-certificate -q http://www.cs.ubc.ca/~humaira/code/fgmpi-2.0.tar.gz
            tar -C $TRAVIS_ROOT -xzf fgmpi-2.0.tar.gz
            cd $TRAVIS_ROOT/fgmpi-2.0
            mkdir build && cd build
            # Clang defaults to C99, which chokes on "Set_PROC_NULL" (fixed in Git now)
            # -Wno-macro-redefined silences numerous instances of the same warning.
            ../configure --prefix=$TRAVIS_ROOT/fgmpi \
                         CFLAGS="-std=gnu89 -Wno-macro-redefined" FC=false CXX=false \
                         --disable-fortran --disable-cxx --disable-romio
            ;;
        linux)
            git clone --depth 10 https://github.com/humairakamal/fgmpi.git fgmpi-source
            cd $TRAVIS_ROOT/fgmpi-source
            ./autogen.sh
            mkdir build && cd build
            # -Wno-macro-redefined silences numerous instances of the same warning.
            ../configure --prefix=$TRAVIS_ROOT/fgmpi \
                         CFLAGS="-std=c99 -Wno-macro-redefined" FC=false CXX=false \
                         --disable-fortran --disable-cxx --disable-romio
            ;;
    esac
    make
    make install
else
    echo "FG-MPI installed..."
    find $TRAVIS_ROOT/fgmpi -name mpiexec
    find $TRAVIS_ROOT/fgmpi -name mpicc
    mpicc -show
fi
