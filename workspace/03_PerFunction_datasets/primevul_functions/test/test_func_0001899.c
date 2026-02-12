const FunctionDef* FunctionLibraryDefinition::GetAttrImpl(
    const NodeDef& ndef) const {
  if (ndef.op() != kGradientOp) {


    return Find(ndef.op());
  }


  const NameAttrList* forward_func_attrs;
  if (!TryGetNodeAttr(ndef, kFuncAttr, &forward_func_attrs)) {
    return nullptr;
  }
  const string& func_name = forward_func_attrs->name();
  {
    tf_shared_lock l(mu_);
    const string& grad_name = FindGradientHelper(func_name);


    if (!grad_name.empty()) {
      if (const auto helper = FindHelper(grad_name)) {
        return &(helper->fdef);
      } else {
        return nullptr;
      }
    }
    if (const auto helper = FindHelper(func_name)) {
      return &(helper->fdef);
    } else {
      return nullptr;
    }
  }
}
