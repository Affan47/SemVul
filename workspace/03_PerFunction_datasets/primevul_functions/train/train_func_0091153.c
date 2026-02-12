hermesBuiltinCopyRestArgs(void *, Runtime *runtime, NativeArgs args) {
  GCScopeMarkerRAII marker{runtime};


  auto frames = runtime->getStackFrames();
  auto it = frames.begin();
  ++it;

  if (LLVM_UNLIKELY(it == frames.end()))
    return HermesValue::encodeUndefinedValue();


  if (!args.getArg(0).isNumber())
    return HermesValue::encodeUndefinedValue();
  uint32_t from = truncateToUInt32(args.getArg(0).getNumber());

  uint32_t argCount = it->getArgCount();
  uint32_t length = from <= argCount ? argCount - from : 0;

  auto cr = JSArray::create(runtime, length, length);
  if (LLVM_UNLIKELY(cr == ExecutionStatus::EXCEPTION))
    return ExecutionStatus::EXCEPTION;
  auto array = runtime->makeHandle(std::move(*cr));
  JSArray::setStorageEndIndex(array, runtime, length);

  for (uint32_t i = 0; i != length; ++i) {
    array->unsafeSetExistingElementAt(
        array.get(), runtime, i, it->getArgRef(from));
    ++from;
  }

  return array.getHermesValue();
}
