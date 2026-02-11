LowLevelCodeDeleteEvent(Address from) {
  if (log_->ll_output_handle_ == NULL) return;
  LowLevelCodeDeleteStruct event;
  event.address = from + Code::kHeaderSize;
  LowLevelLogWriteStruct(event);
}
