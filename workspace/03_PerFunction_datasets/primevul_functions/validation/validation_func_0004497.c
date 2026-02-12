void TfLiteTensorRealloc(size_t num_bytes, TfLiteTensor* tensor) {
  if (tensor->allocation_type != kTfLiteDynamic &&
      tensor->allocation_type != kTfLitePersistentRo) {
    return;
  }

  if (!tensor->data.raw) {
    tensor->data.raw = malloc(num_bytes);
  } else if (num_bytes > tensor->bytes) {
    tensor->data.raw = realloc(tensor->data.raw, num_bytes);
  }
  tensor->bytes = num_bytes;
}
