hermesBuiltinArraySpread(void *, Runtime *runtime, NativeArgs args) {
  Handle<JSArray> target = args.dyncastArg<JSArray>(0);

  if (!target) {
    return runtime->raiseTypeError(
        "HermesBuiltin.arraySpread requires an array target");
  }

  MutableHandle<> nextValue{runtime};

  Handle<JSArray> arr = args.dyncastArg<JSArray>(1);
  if (arr) {


    NamedPropertyDescriptor desc;
    PseudoHandle<JSObject> propObj =
        createPseudoHandle(JSObject::getNamedDescriptor(
            arr,
            runtime,
            Predefined::getSymbolID(Predefined::SymbolIterator),
            desc));
    if (LLVM_LIKELY(propObj) && LLVM_LIKELY(!desc.flags.proxyObject)) {
      PseudoHandle<> slotValue = createPseudoHandle(
          JSObject::getNamedSlotValue(propObj.get(), runtime, desc));
      propObj.invalidate();
      if (LLVM_LIKELY(
              slotValue->getRaw() == runtime->arrayPrototypeValues.getRaw())) {
        slotValue.invalidate();
        auto nextIndex = args.getArg(2).getNumberAs<JSArray::size_type>();
        MutableHandle<> idxHandle{runtime};
        for (JSArray::size_type i = 0; i < JSArray::getLength(*arr); ++i) {

          nextValue = arr->at(runtime, i);
          if (LLVM_UNLIKELY(nextValue->isEmpty())) {


            GCScopeMarkerRAII marker{runtime};
            idxHandle = HermesValue::encodeNumberValue(i);
            CallResult<HermesValue> valueRes =
                JSObject::getComputed_RJS(arr, runtime, idxHandle);
            if (LLVM_UNLIKELY(valueRes == ExecutionStatus::EXCEPTION)) {
              return ExecutionStatus::EXCEPTION;
            }
            nextValue = *valueRes;
          }


          JSArray::setElementAt(target, runtime, nextIndex, nextValue);
          ++nextIndex;
        }

        if (LLVM_UNLIKELY(
                JSArray::setLengthProperty(target, runtime, nextIndex) ==
                ExecutionStatus::EXCEPTION)) {
          return ExecutionStatus::EXCEPTION;
        }

        return HermesValue::encodeNumberValue(nextIndex);
      }
    }
  }


  auto iteratorRecordRes = getIterator(runtime, args.getArgHandle(1));
  if (LLVM_UNLIKELY(iteratorRecordRes == ExecutionStatus::EXCEPTION)) {
    return ExecutionStatus::EXCEPTION;
  }
  IteratorRecord iteratorRecord = *iteratorRecordRes;

  MutableHandle<> nextIndex{runtime, args.getArg(2)};


  for (GCScopeMarkerRAII marker{runtime}; ; marker.flush()) {

    auto nextRes = iteratorStep(runtime, iteratorRecord);
    if (LLVM_UNLIKELY(nextRes == ExecutionStatus::EXCEPTION)) {
      return ExecutionStatus::EXCEPTION;
    }
    Handle<JSObject> next = *nextRes;


    if (!next) {
      return nextIndex.getHermesValue();
    }

    auto nextItemRes = JSObject::getNamed_RJS(
        next, runtime, Predefined::getSymbolID(Predefined::value));
    if (LLVM_UNLIKELY(nextItemRes == ExecutionStatus::EXCEPTION)) {
      return ExecutionStatus::EXCEPTION;
    }
    nextValue = *nextItemRes;


    if (LLVM_UNLIKELY(
            JSArray::putComputed_RJS(target, runtime, nextIndex, nextValue) ==
            ExecutionStatus::EXCEPTION)) {
      return ExecutionStatus::EXCEPTION;
    }


    nextIndex = HermesValue::encodeNumberValue(nextIndex->getNumber() + 1);
  }

  return nextIndex.getHermesValue();
}
