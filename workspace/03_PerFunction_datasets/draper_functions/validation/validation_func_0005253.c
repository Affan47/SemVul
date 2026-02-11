MoveEventInternal(LogEventsAndTags event,
                               Address from,
                               Address to) {
  static Address prev_to_ = NULL;
  if (!Log::IsEnabled() || !FLAG_log_code) return;
  LogMessageBuilder msg;
  msg.Append("%s,", log_events_[event]);
  msg.AppendAddress(from);
  msg.Append(',');
  msg.AppendAddress(to, prev_to_);
  prev_to_ = to;
  if (FLAG_compress_log) {
    ASSERT(compression_helper_ != NULL);
    if (!compression_helper_->HandleMessage(&msg)) return;
  }
  msg.Append('\n');
  msg.WriteToLogFile();
}
