DecodeWebPHeaders(WebPIDecoder* const idec) {
  MemBuffer* const mem = &idec->mem_;
  const uint8_t* data = mem->buf_ + mem->start_;
  size_t curr_size = MemDataSize(mem);
  VP8StatusCode status;
  WebPHeaderStructure headers;

  headers.data = data;
  headers.data_size = curr_size;
  headers.have_all_data = 0;
  status = WebPParseHeaders(&headers);
  if (status == VP8_STATUS_NOT_ENOUGH_DATA) {
    return VP8_STATUS_SUSPENDED;
  } else if (status != VP8_STATUS_OK) {
    return IDecError(idec, status);
  }

  idec->chunk_size_ = headers.compressed_size;
  idec->is_lossless_ = headers.is_lossless;
  if (!idec->is_lossless_) {
    VP8Decoder* const dec = VP8New();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    idec->dec_ = dec;
    dec->alpha_data_ = headers.alpha_data;
    dec->alpha_data_size_ = headers.alpha_data_size;
    ChangeState(idec, STATE_VP8_HEADER, headers.offset);
  } else {
    VP8LDecoder* const dec = VP8LNew();
    if (dec == NULL) {
      return VP8_STATUS_OUT_OF_MEMORY;
    }
    idec->dec_ = dec;
    ChangeState(idec, STATE_VP8L_HEADER, headers.offset);
  }
  return VP8_STATUS_OK;
}
