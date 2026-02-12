CallResult<PseudoHandle<>> JSObject::getNamedOrIndexed(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    SymbolID name,
    PropOpFlags opFlags) {
  if (LLVM_UNLIKELY(selfHandle->flags_.indexedStorage)) {


    const auto strView =
        runtime->getIdentifierTable().getStringView(runtime, name);
    if (auto nameAsIndex = toArrayIndex(strView)) {
      return getComputed_RJS(
          selfHandle,
          runtime,
          runtime->makeHandle(HermesValue::encodeNumberValue(*nameAsIndex)));
    }


  }
  return getNamed_RJS(selfHandle, runtime, name, opFlags);
}
