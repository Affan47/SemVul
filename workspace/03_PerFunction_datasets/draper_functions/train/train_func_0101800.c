FindCodeInCache(Code** code_out) {
  int index = Heap::code_stubs()->FindEntry(GetKey());
  if (index != NumberDictionary::kNotFound) {
    *code_out = Code::cast(Heap::code_stubs()->ValueAt(index));
    return true;
  }
  return false;
}
