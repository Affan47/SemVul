CtPtr ProtocolV1::read_message_data_prepare() {
  ldout(cct, 20) << __func__ << dendl;

  unsigned data_len = current_header.data_len;
  unsigned data_off = current_header.data_off;

  if (data_len) {

#if 0


    map<ceph_tid_t, pair<bufferlist, int> >::iterator p =
        connection->rx_buffers.find(current_header.tid);
    if (p != connection->rx_buffers.end()) {
      ldout(cct, 10) << __func__ << " seleting rx buffer v " << p->second.second
                     << " at offset " << data_off << " len "
                     << p->second.first.length() << dendl;
      data_buf = p->second.first;

      if (data_buf.length() < data_len)
        data_buf.push_back(buffer::create(data_len - data_buf.length()));
      data_blp = data_buf.begin();
    } else {
      ldout(cct, 20) << __func__ << " allocating new rx buffer at offset "
                     << data_off << dendl;
      alloc_aligned_buffer(data_buf, data_len, data_off);
      data_blp = data_buf.begin();
    }
#else
    ldout(cct, 20) << __func__ << " allocating new rx buffer at offset "
		   << data_off << dendl;
    alloc_aligned_buffer(data_buf, data_len, data_off);
    data_blp = data_buf.begin();
#endif
  }

  msg_left = data_len;

  return CONTINUE(read_message_data);
}
