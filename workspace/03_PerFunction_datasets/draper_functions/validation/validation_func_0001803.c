CodeMoveEvent(Address from, Address to) {
  CodeEventsContainer evt_rec;
  CodeMoveEventRecord* rec = &evt_rec.CodeMoveEventRecord_;
  rec->type = CodeEventRecord::CODE_MOVE;
  rec->order = ++enqueue_order_;
  rec->from = from;
  rec->to = to;
  events_buffer_.Enqueue(evt_rec);
}
