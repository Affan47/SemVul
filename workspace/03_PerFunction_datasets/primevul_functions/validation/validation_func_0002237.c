CallResult<bool> JSObject::hasComputed(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    Handle<> nameValHandle) {


  if (selfHandle->flags_.fastIndexProperties) {
    if (auto arrayIndex = toArrayIndexFastPath(*nameValHandle)) {

      if (haveOwnIndexed(selfHandle.get(), runtime, *arrayIndex)) {
        return true;
      }
    }
  }


  auto converted = toPropertyKeyIfObject(runtime, nameValHandle);
  if (LLVM_UNLIKELY(converted == ExecutionStatus::EXCEPTION)) {
    return ExecutionStatus::EXCEPTION;
  }
  auto nameValPrimitiveHandle = *converted;

  ComputedPropertyDescriptor desc;
  MutableHandle<JSObject> propObj{runtime};
  if (getComputedPrimitiveDescriptor(
          selfHandle, runtime, nameValPrimitiveHandle, propObj, desc) ==
      ExecutionStatus::EXCEPTION) {
    return ExecutionStatus::EXCEPTION;
  }
  if (!propObj) {
    return false;
  }
  if (LLVM_UNLIKELY(desc.flags.proxyObject)) {
    CallResult<Handle<>> key = toPropertyKey(runtime, nameValPrimitiveHandle);
    if (key == ExecutionStatus::EXCEPTION)
      return ExecutionStatus::EXCEPTION;
    return JSProxy::hasComputed(propObj, runtime, *key);
  }


  return true;
}
