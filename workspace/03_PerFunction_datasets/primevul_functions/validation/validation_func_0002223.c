CallResult<bool> JSObject::defineOwnComputedPrimitive(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    Handle<> nameValHandle,
    DefinePropertyFlags dpFlags,
    Handle<> valueOrAccessor,
    PropOpFlags opFlags) {
  assert(
      !nameValHandle->isObject() &&
      "nameValHandle passed to "
      "defineOwnComputedPrimitive() cannot be "
      "an object");
  assert(
      !opFlags.getMustExist() && "cannot use mustExist with defineOwnProperty");
  assert(
      !(dpFlags.setValue && dpFlags.isAccessor()) &&
      "Cannot set both value and accessor");
  assert(
      (dpFlags.setValue || dpFlags.isAccessor() ||
       valueOrAccessor.get().isUndefined()) &&
      "value must be undefined when all of setValue/setSetter/setGetter are "
      "false");
  assert(
      !dpFlags.enableInternalSetter &&
      "Cannot set internalSetter on a computed property");
#ifndef NDEBUG
  if (dpFlags.isAccessor()) {
    assert(valueOrAccessor.get().isPointer() && "accessor must be non-empty");
    assert(
        !dpFlags.setWritable && !dpFlags.writable &&
        "writable must not be set with accessors");
  }
#endif


  OptValue<uint32_t> arrayIndex;


  if (selfHandle->flags_.indexedStorage) {
    MutableHandle<StringPrimitive> strPrim{runtime};
    TO_ARRAY_INDEX(runtime, nameValHandle, strPrim, arrayIndex);
  }

  SymbolID id{};


  if (!arrayIndex) {
    LAZY_TO_IDENTIFIER(runtime, nameValHandle, id);
    return defineOwnProperty(
        selfHandle, runtime, id, dpFlags, valueOrAccessor, opFlags);
  }


  if (selfHandle->clazz_.get(runtime)->getHasIndexLikeProperties()) {
    LAZY_TO_IDENTIFIER(runtime, nameValHandle, id);

    NamedPropertyDescriptor desc;
    auto pos = findProperty(selfHandle, runtime, id, desc);

    if (pos) {
      return updateOwnProperty(
          selfHandle,
          runtime,
          id,
          *pos,
          desc,
          dpFlags,
          valueOrAccessor,
          opFlags);
    }
  }


  auto indexedPropPresent =
      getOwnIndexedPropertyFlags(selfHandle.get(), runtime, *arrayIndex);
  if (indexedPropPresent) {

    HermesValue curValueOrAccessor =
        getOwnIndexed(selfHandle.get(), runtime, *arrayIndex);

    auto updateStatus = checkPropertyUpdate(
        runtime,
        *indexedPropPresent,
        dpFlags,
        curValueOrAccessor,
        valueOrAccessor,
        opFlags);
    if (updateStatus == ExecutionStatus::EXCEPTION)
      return ExecutionStatus::EXCEPTION;
    if (updateStatus->first == PropertyUpdateStatus::failed)
      return false;


    if (updateStatus->second == *indexedPropPresent) {

      if (updateStatus->first == PropertyUpdateStatus::done)
        return true;


      auto result =
          setOwnIndexed(selfHandle, runtime, *arrayIndex, valueOrAccessor);
      if (LLVM_UNLIKELY(result == ExecutionStatus::EXCEPTION))
        return ExecutionStatus::EXCEPTION;
      if (*result)
        return true;

      if (opFlags.getThrowOnError()) {

        return runtime->raiseTypeError(
            "cannot change read-only property value");
      }

      return false;
    }


    MutableHandle<> value{runtime};
    if (dpFlags.setValue || dpFlags.isAccessor()) {
      value = valueOrAccessor.get();
    } else {
      value = curValueOrAccessor;
    }


    dpFlags.setEnumerable = 1;
    dpFlags.setWritable = 1;
    dpFlags.setConfigurable = 1;
    dpFlags.enumerable = updateStatus->second.enumerable;
    dpFlags.writable = updateStatus->second.writable;
    dpFlags.configurable = updateStatus->second.configurable;


    if (!deleteOwnIndexed(selfHandle, runtime, *arrayIndex)) {
      if (opFlags.getThrowOnError()) {

        return runtime->raiseTypeError("Cannot define property");
      }
      return false;
    }


    LAZY_TO_IDENTIFIER(runtime, nameValHandle, id);
    return addOwnProperty(selfHandle, runtime, id, dpFlags, value, opFlags);
  }


  if (!selfHandle->isExtensible()) {
    if (opFlags.getThrowOnError()) {
      return runtime->raiseTypeError(
          "cannot add a new property");
    }
    return false;
  }


  bool updateLength = false;
  if (auto arrayHandle = Handle<JSArray>::dyn_vmcast(selfHandle)) {
    if (LLVM_UNLIKELY(*arrayIndex >= JSArray::getLength(*arrayHandle))) {
      NamedPropertyDescriptor lengthDesc;
      bool lengthPresent = getOwnNamedDescriptor(
          arrayHandle,
          runtime,
          Predefined::getSymbolID(Predefined::length),
          lengthDesc);
      (void)lengthPresent;
      assert(lengthPresent && ".length must be present in JSArray");

      if (!lengthDesc.flags.writable) {
        if (opFlags.getThrowOnError()) {
          return runtime->raiseTypeError(
              "Cannot assign to read-only 'length' property of array");
        }
        return false;
      }

      updateLength = true;
    }
  }

  bool newIsIndexed = canNewPropertyBeIndexed(dpFlags);
  if (newIsIndexed) {
    auto result = setOwnIndexed(
        selfHandle,
        runtime,
        *arrayIndex,
        dpFlags.setValue ? valueOrAccessor : Runtime::getUndefinedValue());
    if (LLVM_UNLIKELY(result == ExecutionStatus::EXCEPTION))
      return ExecutionStatus::EXCEPTION;
    if (!*result) {
      if (opFlags.getThrowOnError()) {

        return runtime->raiseTypeError("Cannot define property");
      }
      return false;
    }
  }


  if (updateLength) {

    auto res = JSArray::setLength(
        Handle<JSArray>::vmcast(selfHandle), runtime, *arrayIndex + 1, opFlags);
    (void)res;
    assert(
        res != ExecutionStatus::EXCEPTION && *res &&
        "JSArray::setLength() failed unexpectedly");
  }

  if (newIsIndexed)
    return true;


  LAZY_TO_IDENTIFIER(runtime, nameValHandle, id);
  return addOwnProperty(
      selfHandle, runtime, id, dpFlags, valueOrAccessor, opFlags);
}
