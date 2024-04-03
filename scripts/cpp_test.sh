SCRIPT_DIR=$(realpath $(dirname ${BASH_SOURCE[0]}))
source ${SCRIPT_DIR}/env.source


BUILD_DIR=${OAT_HOME}/build
# cmake -S ${OAT_HOME} -B ${BUILD_DIR} 
cmake  --build ${BUILD_DIR}  -j16

CPP_TEST_DIR=${OAT_HOME}/tests/cpp
CPP_TEST_BUILD_DIR=${CPP_TEST_DIR}/build


cd  ${CPP_TEST_DIR}
# cmake -S ${CPP_TEST_DIR} -B ${CPP_TEST_BUILD_DIR}
cmake  --build ${CPP_TEST_BUILD_DIR}  -j16
cd -

cd ${CPP_TEST_BUILD_DIR} 
./oat_test
cd -