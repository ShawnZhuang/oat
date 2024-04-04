
#include <gtest/gtest.h>
#include <tvm/relay/dataflow_matcher.h>
#include <tvm/relay/dataflow_pattern.h>
#include <tvm/relay/function.h>
#include <tvm/relay/parser.h>
#include <tvm/relay/transform.h>
#include <tvm/relay/onnx/printer.h>
#include <tvm/relay/attrs/nn.h>
#include <tvm/node/reflection.h>

namespace tvm {
namespace relay {

TEST(ProtoBuf, SimpleTest) {
  constexpr const char* kModel = R"(
    #[version = "0.0.5"]
    def @main(%data : Tensor[(1, 304, 128, 128), float32],
             %weight1 : Tensor[(304, 1, 3, 3), float32],
             %bias1 : Tensor[(304), float32],
             %weight2 : Tensor[(256, 304, 1, 1), float32],
             %bias2 : Tensor[(256), float32]) -> Tensor[(1, 256, 128, 128), float32] {
      %0 = nn.conv2d(%data, %weight1, padding=[1, 1, 1, 1], groups=304, channels=304, kernel_size=[3, 3]);
      %1 = nn.bias_add(%0, %bias1);
      %2 = nn.relu(%1);
      %3 = nn.conv2d(%2, %weight2, padding=[0, 0, 0, 0], channels=256, kernel_size=[1, 1]);
      %4 = nn.bias_add(%3, %bias2);
      nn.relu(%4)
    }
  )";

  IRModule module = ParseModule("string", kModel);
  auto opti = transform::Sequential({transform::InferType()});
  opti(module);
  auto func = module->Lookup("main");
  relay::SaveAsOnnx(func, "simple.onnx");
}
TEST(ProtoBuf, SimpleTestConv) {
  Expr var =
      relay::Var("input", TensorType({4, 56, 56, 32}, DataType::Float(16)));
  auto weight = relay::Constant(runtime::NDArray::Empty(
      {64, 3, 3, 32}, DataType::Float(16), {kDLCPU, 0}));

  auto attrs_obj = tvm::ReflectionVTable::Global()->CreateObject(
      relay::Conv2DAttrs::_type_key, {{"strides", Array<Integer>({1, 1})},
                                      {"kernel_size", Array<Integer>({3, 3})},
                                      {"data_layout", String("NHWC")},
                                      {"kernel_layout", String("OHWI")}});
  auto conv =
      Call(Op::Get("nn.conv2d"), {var, weight}, Downcast<Attrs>(attrs_obj));
  auto module = IRModule::FromExpr(conv);

  auto opti = transform::Sequential({transform::InferType()});
  module = opti(module);
  auto func = module->Lookup("main");
  LOG_INFO << PrettyPrint(func);
  relay::SaveAsOnnx(func, "simple2.onnx");
}

}  // namespace relay
}  // namespace tvm