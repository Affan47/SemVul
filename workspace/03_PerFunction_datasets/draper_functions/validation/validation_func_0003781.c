getOrInsertFunction(StringRef Name,
                                      const Type *RetTy, ...) {
  va_list Args;
  va_start(Args, RetTy);


  std::vector<const Type*> ArgTys;
  while (const Type *ArgTy = va_arg(Args, const Type*))
    ArgTys.push_back(ArgTy);

  va_end(Args);


  return getOrInsertFunction(Name,
                             FunctionType::get(RetTy, ArgTys, false),
                             AttrListPtr::get((AttributeWithIndex *)0, 0));
}
