static ExecutionStatus raiseErrorForOverridingStaticBuiltin(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    Handle<SymbolID> name) {
  Handle<StringPrimitive> methodNameHnd =
      runtime->makeHandle(runtime->getStringPrimFromSymbolID(name.get()));


  NamedPropertyDescriptor desc;
  auto *obj = JSObject::getNamedDescriptor(
      selfHandle, runtime, Predefined::getSymbolID(Predefined::name), desc);
  assert(
      !selfHandle->isProxyObject() &&
      "raiseErrorForOverridingStaticBuiltin cannot be used with proxy objects");

  if (!obj || desc.flags.accessor) {
    return runtime->raiseTypeError(
        TwineChar16("Attempting to override read-only builtin method '") +
        TwineChar16(methodNameHnd.get()) + "'");
  }


  StringPrimitive *objName = dyn_vmcast<StringPrimitive>(
      JSObject::getNamedSlotValue(selfHandle.get(), runtime, desc));
  if (!objName) {
    return runtime->raiseTypeError(
        TwineChar16("Attempting to override read-only builtin method '") +
        TwineChar16(methodNameHnd.get()) + "'");
  }

  return runtime->raiseTypeError(
      TwineChar16("Attempting to override read-only builtin method '") +
      TwineChar16(objName) + "." + TwineChar16(methodNameHnd.get()) + "'");
}
