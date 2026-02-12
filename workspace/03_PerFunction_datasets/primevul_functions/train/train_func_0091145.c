CallResult<HermesValue> copyDataPropertiesSlowPath_RJS(
    Runtime *runtime,
    Handle<JSObject> target,
    Handle<JSObject> from,
    Handle<JSObject> excludedItems) {
  assert(
      from->isProxyObject() &&
      "copyDataPropertiesSlowPath_RJS is only for Proxy");


  auto cr = JSProxy::getOwnPropertyKeys(
      from,
      runtime,
      OwnKeysFlags()
          .plusIncludeSymbols()
          .plusIncludeNonSymbols()
          .plusIncludeNonEnumerable());
  if (LLVM_UNLIKELY(cr == ExecutionStatus::EXCEPTION)) {
    return ExecutionStatus::EXCEPTION;
  }
  auto keys = *cr;

  MutableHandle<> nextKeyHandle{runtime};
  MutableHandle<> propValueHandle{runtime};
  GCScopeMarkerRAII marker{runtime};

  for (uint32_t nextKeyIdx = 0, endIdx = keys->getEndIndex();
       nextKeyIdx < endIdx;
       ++nextKeyIdx) {
    marker.flush();
    nextKeyHandle = keys->at(runtime, nextKeyIdx);


    if (excludedItems) {
      assert(
          !excludedItems->isProxyObject() &&
          "internal excludedItems object is a proxy");
      ComputedPropertyDescriptor desc;
      CallResult<bool> cr = JSObject::getOwnComputedPrimitiveDescriptor(
          excludedItems,
          runtime,
          nextKeyHandle,
          JSObject::IgnoreProxy::Yes,
          desc);
      if (LLVM_UNLIKELY(cr == ExecutionStatus::EXCEPTION))
        return ExecutionStatus::EXCEPTION;
      if (*cr)
        continue;
    }


    ComputedPropertyDescriptor desc;
    CallResult<bool> crb =
        JSProxy::getOwnProperty(from, runtime, nextKeyHandle, desc, nullptr);
    if (LLVM_UNLIKELY(cr == ExecutionStatus::EXCEPTION))
      return ExecutionStatus::EXCEPTION;

    if (*crb && desc.flags.enumerable) {

      CallResult<HermesValue> crv =
          JSProxy::getComputed(from, runtime, nextKeyHandle, from);
      if (LLVM_UNLIKELY(crv == ExecutionStatus::EXCEPTION))
        return ExecutionStatus::EXCEPTION;
      propValueHandle = *crv;

      crb = JSObject::defineOwnComputed(
          target,
          runtime,
          nextKeyHandle,
          DefinePropertyFlags::getDefaultNewPropertyFlags(),
          propValueHandle);
      if (LLVM_UNLIKELY(cr == ExecutionStatus::EXCEPTION))
        return ExecutionStatus::EXCEPTION;
      assert(
          crb != ExecutionStatus::EXCEPTION && *crb &&
          "CreateDataProperty failed");
    }
  }
  return target.getHermesValue();
}
