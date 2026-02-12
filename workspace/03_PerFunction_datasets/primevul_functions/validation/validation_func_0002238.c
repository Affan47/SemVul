JSObject *JSObject::getNamedDescriptor(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    SymbolID name,
    PropertyFlags expectedFlags,
    NamedPropertyDescriptor &desc) {
  if (findProperty(selfHandle, runtime, name, expectedFlags, desc))
    return *selfHandle;


  if (LLVM_UNLIKELY(selfHandle->flags_.hostObject)) {
    desc.flags.hostObject = true;
    desc.flags.writable = true;
    return *selfHandle;
  }

  if (LLVM_UNLIKELY(selfHandle->flags_.lazyObject)) {
    assert(
        !selfHandle->flags_.proxyObject &&
        "Proxy objects should never be lazy");

    JSObject::initializeLazyObject(runtime, selfHandle);

    if (findProperty(selfHandle, runtime, name, expectedFlags, desc))
      return *selfHandle;
  }

  if (LLVM_UNLIKELY(selfHandle->flags_.proxyObject)) {
    desc.flags.proxyObject = true;
    return *selfHandle;
  }

  if (selfHandle->parent_) {
    MutableHandle<JSObject> mutableSelfHandle{
        runtime, selfHandle->parent_.getNonNull(runtime)};

    do {

      if (LLVM_LIKELY(
              !mutableSelfHandle->flags_.lazyObject &&
              !mutableSelfHandle->flags_.hostObject &&
              !mutableSelfHandle->flags_.proxyObject)) {
      findProp:
        if (findProperty(
                mutableSelfHandle,
                runtime,
                name,
                PropertyFlags::invalid(),
                desc)) {
          assert(
              !selfHandle->flags_.proxyObject &&
              "Proxy object parents should never have own properties");
          return *mutableSelfHandle;
        }
      } else if (LLVM_UNLIKELY(mutableSelfHandle->flags_.lazyObject)) {
        JSObject::initializeLazyObject(runtime, mutableSelfHandle);
        goto findProp;
      } else if (LLVM_UNLIKELY(mutableSelfHandle->flags_.hostObject)) {
        desc.flags.hostObject = true;
        desc.flags.writable = true;
        return *mutableSelfHandle;
      } else {
        assert(
            mutableSelfHandle->flags_.proxyObject &&
            "descriptor flags are impossible");
        desc.flags.proxyObject = true;
        return *mutableSelfHandle;
      }
    } while ((mutableSelfHandle = mutableSelfHandle->parent_.get(runtime)));
  }

  return nullptr;
}
