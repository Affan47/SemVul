onHttpHeaderComplete(bool chunked, size_t& data_size) {
  if (data_size == SIZE_UNKNOWN) {
    data_size = 0;
  }
  ASSERT(current_ != NULL);
  bool custom_document = false;
  server_->SignalHttpRequestHeader(server_, current_, &custom_document);
  if (!custom_document) {
    current_->request.document.reset(new MemoryStream);
  }
  return HE_NONE;
}
