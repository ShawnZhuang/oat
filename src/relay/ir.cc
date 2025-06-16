#include <tvm/ir/expr.h>

namespace tvm {

class SymbolDimNode : public PrimExprNode {
  int64_t vtypical;
  int64_t vmin;
  int64_t vmax;
  void VisitAttrs(AttrVisitor* v) {
    v->Visit("dtype", &dtype);
    v->Visit("vtypical", &vtypical);
    v->Visit("vmin", &vmin);
    v->Visit("vmax", &vmax);
  }

  bool SEqualReduce(const PrimExprNode* other, SEqualReducer equal) const {
    return equal(dtype, other->dtype) && equal(vtypical, other->vtypical) &&
           equal(vmin, other->vmin) && equal(vmax, other->vmax);
  }

  void SHashReduce(SHashReducer hash_reduce) const {
    hash_reduce(dtype);
    hash_reduce(vtypical);
    hash_reduce(vmin);
    hash_reduce(vmax);
  }
  static constexpr const char* _type_key = "SymbolDim";
  TVM_DECLARE_FINAL_OBJECT_INFO(PrimExprNode, PrimExprNode);
}

class SymbolDim : public PrimExpr {
 public:
  /*!
   * \brief Constructor.
   * \param dtype The data type of the value.
   * \param value The internal value.
   * \param span The location of this object in the source code.
   */
  TVM_DLL SymbolDim(DataType dtype, int64_t value, Span span = Span());

  TVM_DEFINE_OBJECT_REF_METHODS(SymbolDim, PrimExpr, SymbolDimNode);
  TVM_DEFINE_OBJECT_REF_COW_METHOD(SymbolDimNode);
};

}  // namespace tvm