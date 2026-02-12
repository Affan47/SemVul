CallResult<uint32_t> appendAllPropertyNames(
    Handle<JSObject> obj,
    Runtime *runtime,
    MutableHandle<BigStorage> &arr,
    uint32_t beginIndex) {
  uint32_t size = beginIndex;


  bool needDedup = false;
  MutableHandle<> prop(runtime);
  MutableHandle<JSObject> head(runtime, obj.get());
  MutableHandle<StringPrimitive> tmpVal{runtime};
  while (head.get()) {
    GCScope gcScope(runtime);


    auto cr =
        JSObject::getOwnPropertyNames(head, runtime, true );
    if (LLVM_UNLIKELY(cr == ExecutionStatus::EXCEPTION)) {
      return ExecutionStatus::EXCEPTION;
    }
    auto enumerableProps = *cr;
    auto marker = gcScope.createMarker();
    for (unsigned i = 0, e = enumerableProps->getEndIndex(); i < e; ++i) {
      gcScope.flushToMarker(marker);
      prop = enumerableProps->at(runtime, i);
      if (!needDedup) {

        if (LLVM_UNLIKELY(
                BigStorage::push_back(arr, runtime, prop) ==
                ExecutionStatus::EXCEPTION)) {
          return ExecutionStatus::EXCEPTION;
        }
        ++size;
        continue;
      }


      bool dupFound = false;
      if (prop->isNumber()) {
        for (uint32_t j = beginIndex; j < size && !dupFound; ++j) {
          HermesValue val = arr->at(j);
          if (val.isNumber()) {
            dupFound = val.getNumber() == prop->getNumber();
          } else {

            tmpVal = val.getString();
            auto valNum = toArrayIndex(
                StringPrimitive::createStringView(runtime, tmpVal));
            dupFound = valNum && valNum.getValue() == prop->getNumber();
          }
        }
      } else {
        for (uint32_t j = beginIndex; j < size && !dupFound; ++j) {
          HermesValue val = arr->at(j);
          if (val.isNumber()) {

            auto propNum = toArrayIndex(StringPrimitive::createStringView(
                runtime, Handle<StringPrimitive>::vmcast(prop)));
            dupFound = propNum && (propNum.getValue() == val.getNumber());
          } else {
            dupFound = val.getString()->equals(prop->getString());
          }
        }
      }
      if (LLVM_LIKELY(!dupFound)) {
        if (LLVM_UNLIKELY(
                BigStorage::push_back(arr, runtime, prop) ==
                ExecutionStatus::EXCEPTION)) {
          return ExecutionStatus::EXCEPTION;
        }
        ++size;
      }
    }

    CallResult<PseudoHandle<JSObject>> parentRes =
        JSObject::getPrototypeOf(head, runtime);
    if (LLVM_UNLIKELY(parentRes == ExecutionStatus::EXCEPTION)) {
      return ExecutionStatus::EXCEPTION;
    }
    head = parentRes->get();
    needDedup = true;
  }
  return size;
}
