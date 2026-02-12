bool IntArgsAndRetvalsOnDevice(EagerOperation* op) {


  return op->Name() == "IteratorGetNext";
}
