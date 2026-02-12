ObjectID JSObject::getObjectID(JSObject *self, Runtime *runtime) {
  if (LLVM_LIKELY(self->flags_.objectID))
    return self->flags_.objectID;


  self->flags_.objectID = runtime->generateNextObjectID();

  if (LLVM_UNLIKELY(!self->flags_.objectID))
    --self->flags_.objectID;
  return self->flags_.objectID;
}
