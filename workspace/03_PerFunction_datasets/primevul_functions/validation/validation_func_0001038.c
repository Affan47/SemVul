static ALWAYS_INLINE void do_var_dump(VariableSerializer& vs,
                                      const Variant& expression) {

  if (!expression.isObject()) {
    vs.incMaxCount();
  }
  vs.serialize(expression, false);
}
