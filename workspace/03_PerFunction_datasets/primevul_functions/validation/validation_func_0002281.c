ExecutionStatus setProtoClasses(
    Runtime *runtime,
    Handle<JSObject> obj,
    MutableHandle<BigStorage> &arr) {


  if (!obj->shouldCacheForIn(runtime)) {
    arr->clear(runtime);
    return ExecutionStatus::RETURNED;
  }
  MutableHandle<JSObject> head(runtime, obj->getParent(runtime));
  MutableHandle<> clazz(runtime);
  GCScopeMarkerRAII marker{runtime};
  while (head.get()) {
    if (!head->shouldCacheForIn(runtime)) {
      arr->clear(runtime);
      return ExecutionStatus::RETURNED;
    }
    if (JSObject::Helper::flags(*head).lazyObject) {


      JSObject::initializeLazyObject(runtime, head);
    }
    clazz = HermesValue::encodeObjectValue(head->getClass(runtime));
    if (LLVM_UNLIKELY(
            BigStorage::push_back(arr, runtime, clazz) ==
            ExecutionStatus::EXCEPTION)) {
      return ExecutionStatus::EXCEPTION;
    }
    head = head->getParent(runtime);
    marker.flush();
  }
  clazz = HermesValue::encodeNullValue();
  return BigStorage::push_back(arr, runtime, clazz);
}
