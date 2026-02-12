void JSObject::initializeLazyObject(
    Runtime *runtime,
    Handle<JSObject> lazyObject) {
  assert(lazyObject->flags_.lazyObject && "object must be lazy");

  lazyObject->flags_.lazyObject = 0;


  assert(vmisa<Callable>(lazyObject.get()) && "unexpected lazy object");
  Callable::defineLazyProperties(Handle<Callable>::vmcast(lazyObject), runtime);
}
