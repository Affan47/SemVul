CallResult<bool> getOwnComputedPrimitiveDescriptorImpl(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    Handle<> nameValHandle,
    JSObject::IgnoreProxy ignoreProxy,
    SymbolID &id,
    ComputedPropertyDescriptor &desc) {
  assert(
      !nameValHandle->isObject() &&
      "nameValHandle passed to "
      "getOwnComputedPrimitiveDescriptor "
      "cannot be an object");


  if (auto arrayIndex = toArrayIndexFastPath(*nameValHandle)) {
    if (JSObject::Helper::flags(*selfHandle).fastIndexProperties) {
      auto res = JSObject::Helper::getOwnIndexedPropertyFlags(
          selfHandle.get(), runtime, *arrayIndex);
      if (res) {

        desc.flags = *res;
        desc.flags.indexed = 1;
        desc.slot = *arrayIndex;
        return true;
      }


      return false;
    }

    if (!selfHandle->getClass(runtime)->getHasIndexLikeProperties() &&
        !selfHandle->isHostObject() && !selfHandle->isLazy() &&
        !selfHandle->isProxyObject()) {


      return false;
    }
  }


  LAZY_TO_IDENTIFIER(runtime, nameValHandle, id);


  if (JSObject::getOwnNamedDescriptor(
          selfHandle,
          runtime,
          id,
          JSObject::Helper::castToNamedPropertyDescriptorRef(desc))) {
    return true;
  }

  if (LLVM_LIKELY(
          !JSObject::Helper::flags(*selfHandle).indexedStorage &&
          !selfHandle->isLazy() && !selfHandle->isProxyObject())) {
    return false;
  }
  MutableHandle<StringPrimitive> strPrim{runtime};


  if (JSObject::Helper::flags(*selfHandle).indexedStorage) {

    OptValue<uint32_t> arrayIndex;


    TO_ARRAY_INDEX(runtime, nameValHandle, strPrim, arrayIndex);

    if (arrayIndex) {
      auto res = JSObject::Helper::getOwnIndexedPropertyFlags(
          selfHandle.get(), runtime, *arrayIndex);
      if (res) {
        desc.flags = *res;
        desc.flags.indexed = 1;
        desc.slot = *arrayIndex;
        return true;
      }
    }
    return false;
  }

  if (selfHandle->isLazy()) {
    JSObject::initializeLazyObject(runtime, selfHandle);
    return JSObject::getOwnComputedPrimitiveDescriptor(
        selfHandle, runtime, nameValHandle, ignoreProxy, desc);
  }

  assert(selfHandle->isProxyObject() && "descriptor flags are impossible");
  if (ignoreProxy == JSObject::IgnoreProxy::Yes) {
    return false;
  }
  return JSProxy::getOwnProperty(
      selfHandle, runtime, nameValHandle, desc, nullptr);
}
