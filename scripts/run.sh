SCRIPT_DIR=$(realpath $(dirname ${BASH_SOURCE[0]}))
source ${SCRIPT_DIR}/env.source


BUILD_DIR=${OAT_HOME}/build
mkdir -p ${BUILD_DIR}
cmake -S ${OAT_HOME} -B ${BUILD_DIR} 
cmake  --build ${BUILD_DIR}  -j16