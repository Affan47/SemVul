void TfLiteTensorRealloc(size_t num_bytes, TfLiteTensor* tensor) {
  if (tensor->allocation_type != kTfLiteDynamic &&
      tensor->allocation_type != kTfLitePersistentRo) {
    return;
  }

  if (!tensor->data.raw) {
    tensor->data.raw = (char*)malloc(num_bytes);
  } else if (num_bytes > tensor->bytes) {
    tensor->data.raw = (char*)realloc(tensor->data.raw, num_bytes);
  }
  tensor->bytes = num_bytes;
}
