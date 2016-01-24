set -e
set -x

TRAVIS_ROOT="$1"
PRK_TARGET="$2"

MPI_IMPL=mpich

echo "PWD=$PWD"

case "$PRK_TARGET" in
    allserial)
        echo "Serial"
        ;;

    allopenmp)
        echo "OpenMP"
        sh ./travis/install-clang.sh $TRAVIS_ROOT omp
        ;;
    allmpi*)
        echo "Any normal MPI"
        sh ./travis/install-clang.sh $TRAVIS_ROOT omp
        sh ./travis/install-mpi.sh $TRAVIS_ROOT $MPI_IMPL
        ;;
    allshmem)
        echo "SHMEM"
        sh ./travis/install-hydra.sh $TRAVIS_ROOT
        sh ./travis/install-libfabric.sh $TRAVIS_ROOT
        sh ./travis/install-sandia-openshmem.sh $TRAVIS_ROOT
        ;;
    allupc)
        echo "UPC"
        case "$UPC_IMPL" in
            gupc)
                # GUPC is working fine
                sh ./travis/install-intrepid-upc.sh $TRAVIS_ROOT
                ;;
            bupc)
                # BUPC is new
                case $GASNET_CONDUIT in
                    ofi)
                        sh ./travis/install-hydra.sh $TRAVIS_ROOT
                        sh ./travis/install-libfabric.sh $TRAVIS_ROOT
                        ;;
                    mpi)
                        sh ./travis/install-mpi.sh $TRAVIS_ROOT $MPI_IMPL
                        ;;
                esac
                sh ./travis/install-berkeley-upc.sh $TRAVIS_ROOT
                ;;
        esac
        ;;
    allcharm++)
        echo "Charm++"
        sh ./travis/install-charm++.sh $TRAVIS_ROOT charm++
        ;;
    allampi)
        echo "Adaptive MPI (AMPI)"
        sh ./travis/install-charm++.sh $TRAVIS_ROOT AMPI
        ;;
    allfgmpi)
        echo "Fine-Grain MPI (FG-MPI)"
        sh ./travis/install-autotools.sh $TRAVIS_ROOT
        sh ./travis/install-fgmpi.sh $TRAVIS_ROOT
        ;;
    allgrappa)
        echo "Grappa"
        sh ./travis/install-cmake.sh $TRAVIS_ROOT
        sh ./travis/install-mpi.sh $TRAVIS_ROOT $MPI_IMPL
        sh ./travis/install-grappa.sh $TRAVIS_ROOT $MPI_IMPL
        ;;
    allchapel)
        echo "Chapel"
        sh ./travis/install-chapel.sh $TRAVIS_ROOT
        ;;
    allhpx5)
        echo "HPX-5"
        sh ./travis/install-autotools.sh $TRAVIS_ROOT
        sh ./travis/install-hpx5.sh $TRAVIS_ROOT
        ;;
esac
