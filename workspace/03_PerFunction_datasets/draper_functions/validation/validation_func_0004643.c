ArrayLengthRangeError(Heap* heap) {
  HandleScope scope(heap->isolate());
  return heap->isolate()->Throw(
      *FACTORY->NewRangeError("invalid_array_length",
          HandleVector<Object>(NULL, 0)));
}
