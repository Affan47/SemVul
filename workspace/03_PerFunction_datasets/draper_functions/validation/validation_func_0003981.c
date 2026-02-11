ComputeLoadGlobal(String* name,
                                          JSObject* receiver,
                                          GlobalObject* holder,
                                          JSGlobalPropertyCell* cell,
                                          bool is_dont_delete) {
  ASSERT(IC::GetCodeCacheForObject(receiver, holder) == OWN_MAP);
  Code::Flags flags = Code::ComputeMonomorphicFlags(Code::LOAD_IC, NORMAL);
  Object* code = receiver->map()->FindInCodeCache(name, flags);
  if (code->IsUndefined()) {
    LoadStubCompiler compiler;
    { MaybeObject* maybe_code = compiler.CompileLoadGlobal(receiver,
                                                           holder,
                                                           cell,
                                                           name,
                                                           is_dont_delete);
      if (!maybe_code->ToObject(&code)) return maybe_code;
    }
    PROFILE(isolate_,
            CodeCreateEvent(Logger::LOAD_IC_TAG, Code::cast(code), name));
    GDBJIT(AddCode(GDBJITInterface::LOAD_IC, name, Code::cast(code)));
    Object* result;
    { MaybeObject* maybe_result =
          receiver->UpdateMapCodeCache(name, Code::cast(code));
      if (!maybe_result->ToObject(&result)) return maybe_result;
    }
  }
  return code;
}
