CallResult<bool> JSObject::deleteNamed(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    SymbolID name,
    PropOpFlags opFlags) {
  assert(
      !opFlags.getMustExist() && "mustExist cannot be specified when deleting");


  NamedPropertyDescriptor desc;
  auto pos = findProperty(selfHandle, runtime, name, desc);


  if (!pos) {
    if (LLVM_LIKELY(
            !selfHandle->flags_.lazyObject &&
            !selfHandle->flags_.proxyObject)) {
      return true;
    } else if (selfHandle->flags_.lazyObject) {

      initializeLazyObject(runtime, selfHandle);
      pos = findProperty(selfHandle, runtime, name, desc);
      if (!pos)
        return true;
    } else {
      assert(selfHandle->flags_.proxyObject && "object flags are impossible");
      return proxyOpFlags(
          runtime,
          opFlags,
          "Proxy delete returned false",
          JSProxy::deleteNamed(selfHandle, runtime, name));
    }
  }

  if (LLVM_UNLIKELY(!desc.flags.configurable)) {
    if (opFlags.getThrowOnError()) {
      return runtime->raiseTypeError(
          TwineChar16("Property '") +
          runtime->getIdentifierTable().getStringViewForDev(runtime, name) +
          "' is not configurable");
    }
    return false;
  }


  setNamedSlotValue(
      *selfHandle, runtime, desc, HermesValue::encodeEmptyValue());


  auto newClazz = HiddenClass::deleteProperty(
      runtime->makeHandle(selfHandle->clazz_), runtime, *pos);
  selfHandle->clazz_.set(runtime, *newClazz, &runtime->getHeap());

  return true;
}
