CallResult<bool> JSObject::setParent(
    JSObject *self,
    Runtime *runtime,
    JSObject *parent,
    PropOpFlags opFlags) {
  if (LLVM_UNLIKELY(self->isProxyObject())) {
    return proxyOpFlags(
        runtime,
        opFlags,
        "Object is not extensible.",
        JSProxy::setPrototypeOf(
            runtime->makeHandle(self), runtime, runtime->makeHandle(parent)));
  }


  if (self->parent_.get(runtime) == parent)
    return true;

  if (!self->isExtensible()) {
    if (opFlags.getThrowOnError()) {
      return runtime->raiseTypeError("Object is not extensible.");
    } else {
      return false;
    }
  }

  for (JSObject *cur = parent; cur; cur = cur->parent_.get(runtime)) {
    if (cur == self) {
      if (opFlags.getThrowOnError()) {
        return runtime->raiseTypeError("Prototype cycle detected");
      } else {
        return false;
      }
    } else if (LLVM_UNLIKELY(cur->isProxyObject())) {


      break;
    }
  }

  self->parent_.set(runtime, parent, &runtime->getHeap());

  return true;
}
