#include <oat/relay/expr_functor.h>
#include <set>
#include <stack>
namespace tvm {
namespace relay {

class TopoOrderVisitor : public ExprVisitor {
 private:
  std::stack<Expr> ordered_exprs_;
  std::set<const ExprNode*> visited_;
  std::function<void(const Expr& e)> forward_;
  std::function<void(const Expr& e)> backward_;

 public:
  TopoOrderVisitor(std::function<void(const Expr& e)> forward,
                   std::function<void(const Expr& e)> backward)
      : forward_(forward), backward_(backward) {}
  ~TopoOrderVisitor() {}
  void Apply(const Expr& e) {
    this->VisitExpr(e);
    if (backward_ != nullptr) {
      while (not ordered_exprs_.empty()) {
        backward_(ordered_exprs_.top());
        ordered_exprs_.pop();
      }
    }
  }
  void VisitExpr(const Expr& e) final {
    if (visited_.count(e.get()) != 0) {
      return;
    };
    visited_.insert(e.get());
    ExprVisitor::VisitExpr(e);
    if (forward_ != nullptr) {
      forward_(e);
    }
    ordered_exprs_.push(e);
  }
};

// TVM_REGISTER_GLOBAL("test").set_body([](TVMArgs args, TVMRetValue* rv) ->
// void {
//   return;
// });
}  // namespace relay
}  // namespace tvm