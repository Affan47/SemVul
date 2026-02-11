TypeCheck(Heap* heap,
                                int argc,
                                Object** argv,
                                FunctionTemplateInfo* info) {
  Object* recv = argv[0];

  if (!recv->IsJSObject()) return heap->null_value();
  Object* sig_obj = info->signature();
  if (sig_obj->IsUndefined()) return recv;
  SignatureInfo* sig = SignatureInfo::cast(sig_obj);

  Object* recv_type = sig->receiver();

  Object* holder = recv;
  if (!recv_type->IsUndefined()) {
    for (; holder != heap->null_value(); holder = holder->GetPrototype()) {
      if (holder->IsInstanceOf(FunctionTemplateInfo::cast(recv_type))) {
        break;
      }
    }
    if (holder == heap->null_value()) return holder;
  }
  Object* args_obj = sig->args();

  if (args_obj->IsUndefined()) return holder;
  FixedArray* args = FixedArray::cast(args_obj);
  int length = args->length();
  if (argc <= length) length = argc - 1;
  for (int i = 0; i < length; i++) {
    Object* argtype = args->get(i);
    if (argtype->IsUndefined()) continue;
    Object** arg = &argv[-1 - i];
    Object* current = *arg;
    for (; current != heap->null_value(); current = current->GetPrototype()) {
      if (current->IsInstanceOf(FunctionTemplateInfo::cast(argtype))) {
        *arg = current;
        break;
      }
    }
    if (current == heap->null_value()) *arg = heap->undefined_value();
  }
  return holder;
}
