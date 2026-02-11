GetCode(PropertyType type,
                                             String* name,
                                             InlineCacheState state) {
  Code::Flags flags =
      Code::ComputeFlags(Code::KEYED_STORE_IC, state, strict_mode_, type);
  MaybeObject* result = GetCodeWithFlags(flags, name);
  if (!result->IsFailure()) {
    PROFILE(isolate(),
            CodeCreateEvent(Logger::KEYED_STORE_IC_TAG,
                            Code::cast(result->ToObjectUnchecked()),
                            name));
    GDBJIT(AddCode(GDBJITInterface::KEYED_STORE_IC,
                   name,
                   Code::cast(result->ToObjectUnchecked())));
  }
  return result;
}
