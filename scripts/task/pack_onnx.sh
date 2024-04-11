TVM_DIR="3rdparty/tvm"
# mv ${TVM_DIR}/include/tvm/relay/onnx/printer.h include/tvm/relay/onnx/printer.h 
# mv ${TVM_DIR}/src/relay/onnx/printer.cc src/relay/onnx/printer.cc
# mv ${TVM_DIR}/tests/cpp/onnx/onnx_printer_test.cc tests/cpp/onnx/onnx_printer_test.cc 

mkdir -p ${TVM_DIR}/include/tvm/relay/onnx/
mkdir -p ${TVM_DIR}/src/relay/onnx/
mkdir -p ${TVM_DIR}/tests/cpp/onnx/
cp include/tvm/relay/onnx/printer.h ${TVM_DIR}/include/tvm/relay/onnx/printer.h
cp src/relay/onnx/printer.cc  ${TVM_DIR}/src/relay/onnx/printer.cc
cp src/relay/onnx/onnx-ml.pb.h  ${TVM_DIR}/src/relay/onnx/onnx-ml.pb.h
cp src/relay/onnx/onnx-ml.pb.cc  ${TVM_DIR}/src/relay/onnx/onnx-ml.pb.cc
# cp src/relay/onnx/onnx-ml.proto  ${TVM_DIR}/src/relay/onnx/onnx-ml.proto
cp tests/cpp/onnx/onnx_printer_test.cc  ${TVM_DIR}/tests/cpp/onnx/onnx_printer_test.cc