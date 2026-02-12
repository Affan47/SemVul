CallResult<bool> JSObject::deleteComputed(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    Handle<> nameValHandle,
    PropOpFlags opFlags) {
  assert(
      !opFlags.getMustExist() && "mustExist cannot be specified when deleting");


  auto converted = toPropertyKeyIfObject(runtime, nameValHandle);
  if (LLVM_UNLIKELY(converted == ExecutionStatus::EXCEPTION)) {
    return ExecutionStatus::EXCEPTION;
  }

  auto nameValPrimitiveHandle = *converted;


  OptValue<uint32_t> arrayIndex;


  if (selfHandle->flags_.indexedStorage) {
    MutableHandle<StringPrimitive> strPrim{runtime};
    TO_ARRAY_INDEX(runtime, nameValPrimitiveHandle, strPrim, arrayIndex);
  }


  if (arrayIndex && selfHandle->flags_.fastIndexProperties) {

    if (deleteOwnIndexed(selfHandle, runtime, *arrayIndex))
      return true;


    if (opFlags.getThrowOnError()) {

      return runtime->raiseTypeError("Cannot delete property");
    }
    return false;
  }


  if (LLVM_UNLIKELY(selfHandle->flags_.lazyObject)) {

    initializeLazyObject(runtime, selfHandle);
    return deleteComputed(selfHandle, runtime, nameValHandle, opFlags);
  }


  SymbolID id;
  LAZY_TO_IDENTIFIER(runtime, nameValPrimitiveHandle, id);


  NamedPropertyDescriptor desc;
  auto pos = findProperty(selfHandle, runtime, id, desc);


  if (pos) {

    if (LLVM_UNLIKELY(!desc.flags.configurable)) {
      if (opFlags.getThrowOnError()) {

        return runtime->raiseTypeError("Property is not configurable");
      }
      return false;
    }
  }


  if (arrayIndex) {
    if (!deleteOwnIndexed(selfHandle, runtime, *arrayIndex)) {

      if (opFlags.getThrowOnError()) {

        return runtime->raiseTypeError("Cannot delete property");
      }
      return false;
    }
  }

  if (pos) {


    setNamedSlotValue(
        *selfHandle, runtime, desc, HermesValue::encodeEmptyValue());


    auto newClazz = HiddenClass::deleteProperty(
        runtime->makeHandle(selfHandle->clazz_), runtime, *pos);
    selfHandle->clazz_.set(runtime, *newClazz, &runtime->getHeap());
  } else if (LLVM_UNLIKELY(selfHandle->flags_.proxyObject)) {
    CallResult<Handle<>> key = toPropertyKey(runtime, nameValPrimitiveHandle);
    if (key == ExecutionStatus::EXCEPTION)
      return ExecutionStatus::EXCEPTION;
    return proxyOpFlags(
        runtime,
        opFlags,
        "Proxy delete returned false",
        JSProxy::deleteComputed(selfHandle, runtime, *key));
  }

  return true;
}
