#ifndef OAT_RELAY_EXPR_FUNCTOR_H_
#define OAT_RELAY_EXPR_FUNCTOR_H_
#include <tvm/relay/expr_functor.h>
namespace tvm {
namespace relay {
#define RELAY_EXPR_TOUCHER_DISPATCH(OP)                                  \
  vtable.template set_dispatch<OP>([](const ObjectRef& n, TSelf* self) { \
    return self->Touch_(static_cast<const OP*>(n.get()));                \
  });

#define EXPR_TOUCHER_TOUCH_DEFAULT \
  { return; }
/*! \brief A non-iterating Expression Rewriter
 *
 *  ExprToucher provides a Touch interface for modifying graphs in Post-DFS
 * order.
 *
 * The expectation is that ExprToucher objects will be passed to
 * PostOrderRewrite, which will non-recursively unroll the graph and call
 * Rewriting on inputs. It will then pass the original node, called `pre`, and a
 * node recreated with any alterned inputs, called `post`, to the ExprToucher.
 * The ExprToucher can then use the information in those two nodes to do more
 * complex graph rewriting.
 */
class ExprToucher {
 private:
  using TSelf = ExprToucher;
  using FType = tvm::NodeFunctor<void(const ObjectRef& n, TSelf* self)>;

 public:
  /*! \brief virtual destructor */
  virtual ~ExprToucher() {}
  /*!
   * \brief Same as call.
   * \param pre The expression node before rewriting.
   * \param post The expression node with rewritten inputs.
   * \return The result of the call
   */
  void operator()(const Expr& pre) { return Touch(pre); }
  /*!
   * \brief The functor call.
   * \param pre The expression node before rewriting.
   * \param post The expression node with rewritten inputs.
   * \return The result of the call
   */
  virtual void Touch(const Expr& pre) {
    ICHECK(pre.defined());
    static FType vtable = InitVTable();
    return vtable(pre, this);
  }
  // Functions that can be overriden by subclass, should not recurse
  virtual void Touch_(const VarNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const GlobalVarNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const ConstantNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const TupleNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const FunctionNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const CallNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const LetNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const IfNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const OpNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const TupleGetItemNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const RefCreateNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const RefReadNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const RefWriteNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const ConstructorNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;
  virtual void Touch_(const MatchNode* pre) EXPR_TOUCHER_TOUCH_DEFAULT;

 private:
  // initialize the vtable.
  static FType InitVTable() {
    FType vtable;
    // Set dispatch
    RELAY_EXPR_TOUCHER_DISPATCH(ConstantNode);
    RELAY_EXPR_TOUCHER_DISPATCH(TupleNode);
    RELAY_EXPR_TOUCHER_DISPATCH(VarNode);
    RELAY_EXPR_TOUCHER_DISPATCH(GlobalVarNode);
    RELAY_EXPR_TOUCHER_DISPATCH(FunctionNode);
    RELAY_EXPR_TOUCHER_DISPATCH(CallNode);
    RELAY_EXPR_TOUCHER_DISPATCH(LetNode);
    RELAY_EXPR_TOUCHER_DISPATCH(IfNode);
    RELAY_EXPR_TOUCHER_DISPATCH(OpNode);
    RELAY_EXPR_TOUCHER_DISPATCH(TupleGetItemNode);
    RELAY_EXPR_TOUCHER_DISPATCH(RefCreateNode);
    RELAY_EXPR_TOUCHER_DISPATCH(RefReadNode);
    RELAY_EXPR_TOUCHER_DISPATCH(RefWriteNode);
    RELAY_EXPR_TOUCHER_DISPATCH(ConstructorNode);
    RELAY_EXPR_TOUCHER_DISPATCH(MatchNode);
    return vtable;
  }
};

}  // namespace relay

}  // namespace tvm
#endif