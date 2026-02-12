CallResult<bool> JSObject::putNamedWithReceiver_RJS(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    SymbolID name,
    Handle<> valueHandle,
    Handle<> receiver,
    PropOpFlags opFlags) {
  NamedPropertyDescriptor desc;


  JSObject *propObj = getNamedDescriptor(
      selfHandle,
      runtime,
      name,
      PropertyFlags::defaultNewNamedPropertyFlags(),
      desc);


  if (propObj) {


    if (LLVM_LIKELY(
            *selfHandle == propObj &&
            selfHandle.getHermesValue().getRaw() == receiver->getRaw() &&
            !desc.flags.accessor && !desc.flags.internalSetter &&
            !desc.flags.hostObject && !desc.flags.proxyObject &&
            desc.flags.writable)) {
      setNamedSlotValue(
          *selfHandle, runtime, desc, valueHandle.getHermesValue());
      return true;
    }

    if (LLVM_UNLIKELY(desc.flags.accessor)) {
      auto *accessor =
          vmcast<PropertyAccessor>(getNamedSlotValue(propObj, runtime, desc));


      if (!accessor->setter) {
        if (opFlags.getThrowOnError()) {
          return runtime->raiseTypeError(
              TwineChar16("Cannot assign to property '") +
              runtime->getIdentifierTable().getStringViewForDev(runtime, name) +
              "' which has only a getter");
        }
        return false;
      }


      if (accessor->setter.get(runtime)->executeCall1(
              runtime->makeHandle(accessor->setter),
              runtime,
              receiver,
              *valueHandle) == ExecutionStatus::EXCEPTION) {
        return ExecutionStatus::EXCEPTION;
      }
      return true;
    }

    if (LLVM_UNLIKELY(desc.flags.proxyObject)) {
      assert(
          !opFlags.getMustExist() &&
          "MustExist cannot be used with Proxy objects");
      CallResult<bool> setRes = JSProxy::setNamed(
          runtime->makeHandle(propObj), runtime, name, valueHandle, receiver);
      if (LLVM_UNLIKELY(setRes == ExecutionStatus::EXCEPTION)) {
        return ExecutionStatus::EXCEPTION;
      }
      if (!*setRes && opFlags.getThrowOnError()) {
        return runtime->raiseTypeError(
            TwineChar16("Proxy set returned false for property '") +
            runtime->getIdentifierTable().getStringView(runtime, name) + "'");
      }
      return setRes;
    }

    if (LLVM_UNLIKELY(!desc.flags.writable)) {
      if (desc.flags.staticBuiltin) {
        return raiseErrorForOverridingStaticBuiltin(
            selfHandle, runtime, runtime->makeHandle(name));
      }
      if (opFlags.getThrowOnError()) {
        return runtime->raiseTypeError(
            TwineChar16("Cannot assign to read-only property '") +
            runtime->getIdentifierTable().getStringViewForDev(runtime, name) +
            "'");
      }
      return false;
    }

    if (*selfHandle == propObj && desc.flags.internalSetter) {
      return internalSetter(
          selfHandle, runtime, name, desc, valueHandle, opFlags);
    }
  }


  MutableHandle<JSObject> receiverHandle{runtime, *selfHandle};
  if (selfHandle.getHermesValue().getRaw() != receiver->getRaw() ||
      receiverHandle->isHostObject() || receiverHandle->isProxyObject()) {
    if (selfHandle.getHermesValue().getRaw() != receiver->getRaw()) {
      receiverHandle = dyn_vmcast<JSObject>(*receiver);
    }
    if (!receiverHandle) {
      return false;
    }

    if (getOwnNamedDescriptor(receiverHandle, runtime, name, desc)) {
      if (LLVM_UNLIKELY(desc.flags.accessor || !desc.flags.writable)) {
        return false;
      }

      assert(
          !receiverHandle->isHostObject() && !receiverHandle->isProxyObject() &&
          "getOwnNamedDescriptor never sets hostObject or proxyObject flags");

      setNamedSlotValue(
          *receiverHandle, runtime, desc, valueHandle.getHermesValue());
      return true;
    }


    if (LLVM_UNLIKELY(
            receiverHandle->isHostObject() ||
            receiverHandle->isProxyObject())) {
      if (receiverHandle->isHostObject()) {
        return vmcast<HostObject>(receiverHandle.get())
            ->set(name, *valueHandle);
      }
      ComputedPropertyDescriptor desc;
      Handle<> nameValHandle = runtime->makeHandle(name);
      CallResult<bool> descDefinedRes = getOwnComputedPrimitiveDescriptor(
          receiverHandle, runtime, nameValHandle, IgnoreProxy::No, desc);
      if (LLVM_UNLIKELY(descDefinedRes == ExecutionStatus::EXCEPTION)) {
        return ExecutionStatus::EXCEPTION;
      }
      DefinePropertyFlags dpf;
      if (*descDefinedRes) {
        dpf.setValue = 1;
      } else {
        dpf = DefinePropertyFlags::getDefaultNewPropertyFlags();
      }
      return JSProxy::defineOwnProperty(
          receiverHandle, runtime, nameValHandle, dpf, valueHandle, opFlags);
    }
  }


  if (LLVM_UNLIKELY(opFlags.getMustExist())) {
    return runtime->raiseReferenceError(
        TwineChar16("Property '") +
        runtime->getIdentifierTable().getStringViewForDev(runtime, name) +
        "' doesn't exist");
  }


  return addOwnProperty(
      receiverHandle,
      runtime,
      name,
      DefinePropertyFlags::getDefaultNewPropertyFlags(),
      valueHandle,
      opFlags);
}
