CallResult<Handle<BigStorage>> getForInPropertyNames(
    Runtime *runtime,
    Handle<JSObject> obj,
    uint32_t &beginIndex,
    uint32_t &endIndex) {
  Handle<HiddenClass> clazz(runtime, obj->getClass(runtime));


  MutableHandle<BigStorage> arr(runtime, clazz->getForInCache(runtime));
  if (arr) {
    beginIndex = matchesProtoClasses(runtime, obj, arr);
    if (beginIndex) {

      endIndex = arr->size();
      return arr;
    }


    clazz->clearForInCache(runtime);

    arr = nullptr;
  }


  auto ownPropEstimate = clazz->getNumProperties();
  auto arrRes = obj->shouldCacheForIn(runtime)
      ? BigStorage::createLongLived(runtime, ownPropEstimate)
      : BigStorage::create(runtime, ownPropEstimate);
  if (LLVM_UNLIKELY(arrRes == ExecutionStatus::EXCEPTION)) {
    return ExecutionStatus::EXCEPTION;
  }
  arr = std::move(*arrRes);
  if (setProtoClasses(runtime, obj, arr) == ExecutionStatus::EXCEPTION) {
    return ExecutionStatus::EXCEPTION;
  }
  beginIndex = arr->size();


  bool canCache = beginIndex;
  auto end = appendAllPropertyNames(obj, runtime, arr, beginIndex);
  if (end == ExecutionStatus::EXCEPTION) {
    return ExecutionStatus::EXCEPTION;
  }
  endIndex = *end;


  const bool tooMuchProto = *end / 4 > ownPropEstimate;
  if (canCache && !tooMuchProto) {
    assert(beginIndex > 0 && "cached array must start with proto classes");
#ifdef HERMES_SLOW_DEBUG
    assert(beginIndex == matchesProtoClasses(runtime, obj, arr) && "matches");
#endif
    clazz->setForInCache(*arr, runtime);
  }
  return arr;
}
