#include <tvm/ir/tensor_type.h>
#include <tvm/node/reflection.h>
#include <tvm/relay/expr.h>
#include <tvm/relay/expr_functor.h>

// #include "../../ir/attr_functor.h"
#include <tvm/ir/attr_functor.h>
#include "onnx-ml.pb.h"

namespace tvm {
namespace name {
namespace onnx_loader {
using namespace onnx;
ObjectRef ParseAttribute(const AttributeProto* proto) {
  // TODO;
  return ObjectRef();
}

class AttrLoader : public AttrVisitor {
 private:
  const std::unordered_map<std::string, const AttributeProto*>& umap_;

 public:
  AttrLoader(const std::unordered_map<std::string, const AttributeProto*>& umap)
      : umap_(umap) {}
  ~AttrLoader() {}
  const AttributeProto* SaveGet(const std::string& attr_name) const {
    ICHECK(umap_.count(attr_name));
    auto proto = umap_.at(attr_name);
    ICHECK(proto != nullptr);
    return proto;
  }
  void Visit(const char* key, double* value) final {
    auto proto = SaveGet(key);
    ICHECK(proto->floats_size() == 1);
    *value = proto->floats(0);
  };
  void Visit(const char* key, int64_t* value) final {
    auto proto = SaveGet(key);
    ICHECK(proto->ints_size() == 1);
    *value = proto->ints(0);
  };
  void Visit(const char* key, uint64_t* value) final {
    auto proto = SaveGet(key);
    ICHECK(proto->ints_size() == 1);
    *value = proto->ints(0);
  };
  void Visit(const char* key, int* value) final {
    auto proto = SaveGet(key);
    ICHECK(proto->ints_size() == 1);
    *value = proto->ints(0);
  };
  void Visit(const char* key, bool* value) final {
    auto proto = SaveGet(key);
    ICHECK(proto->ints_size() == 1);
    *value = proto->ints(0) != 0;
  };
  void Visit(const char* key, std::string* value) final {
    auto proto = SaveGet(key);
    ICHECK(proto->strings_size() == 1);
    *value = proto->strings(0);
  };
  void Visit(const char* key, void** value) final { LOG_FATAL; };
  void Visit(const char* key, DataType* value) final {
    auto proto = SaveGet(key);
    ICHECK(proto->strings_size() == 1);
    auto data_type = proto->strings(0);
    std::transform(data_type.begin(), data_type.end(), data_type.begin(),
                   ::tolower);
    *value = DataType(runtime::String2DLDataType(data_type));
  };
  void Visit(const char* key, runtime::NDArray* value) final { LOG_FATAL; };
  void Visit(const char* key, runtime::ObjectRef* value) final {
    auto ref = ParseAttribute(SaveGet(key));
    *value = ref;
    return;
  };
};

}  // namespace onnx_loader

}  // namespace name

}  // namespace tvm
