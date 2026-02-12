ExecutionStatus JSObject::getComputedPrimitiveDescriptor(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    Handle<> nameValHandle,
    MutableHandle<JSObject> &propObj,
    ComputedPropertyDescriptor &desc) {
  assert(
      !nameValHandle->isObject() &&
      "nameValHandle passed to "
      "getComputedPrimitiveDescriptor cannot "
      "be an object");

  propObj = selfHandle.get();

  SymbolID id{};

  GCScopeMarkerRAII marker{runtime};
  do {


    Handle<JSObject> loopHandle = propObj;

    CallResult<bool> res = getOwnComputedPrimitiveDescriptorImpl(
        loopHandle, runtime, nameValHandle, IgnoreProxy::Yes, id, desc);
    if (LLVM_UNLIKELY(res == ExecutionStatus::EXCEPTION)) {
      return ExecutionStatus::EXCEPTION;
    }
    if (*res) {
      return ExecutionStatus::RETURNED;
    }

    if (LLVM_UNLIKELY(propObj->flags_.hostObject)) {
      desc.flags.hostObject = true;
      desc.flags.writable = true;
      return ExecutionStatus::RETURNED;
    }
    if (LLVM_UNLIKELY(propObj->flags_.proxyObject)) {
      desc.flags.proxyObject = true;
      return ExecutionStatus::RETURNED;
    }


    propObj = propObj->getParent(runtime);


    marker.flush();
  } while (propObj);
  return ExecutionStatus::RETURNED;
}
