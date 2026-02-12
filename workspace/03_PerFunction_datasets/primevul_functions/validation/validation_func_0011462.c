void ProtocolV1::prepare_send_message(uint64_t features, Message *m,
                                      bufferlist &bl) {
  ldout(cct, 20) << __func__ << " m " << *m << dendl;


  ldout(cct, 20) << __func__ << (m->empty_payload() ? " encoding features " : " half-reencoding features ")
		 << features << " " << m  << " " << *m << dendl;


  m->encode(features, messenger->crcflags, true);

  bl.append(m->get_payload());
  bl.append(m->get_middle());
  bl.append(m->get_data());
}
