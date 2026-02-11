ParseCandidates(SignalingProtocol protocol,
                                   const buzz::XmlElement* elem,
                                   Candidates* candidates,
                                   ParseError* error) {
  for (const buzz::XmlElement* cand_elem = elem->FirstElement();
       cand_elem != NULL;
       cand_elem = cand_elem->NextElement()) {
    if (cand_elem->Name() == QN_GINGLE_RAW_CHANNEL) {
      talk_base::SocketAddress addr;
      if (!ParseRawAddress(cand_elem, &addr, error))
        return false;

      Candidate candidate;
      candidate.set_name(cand_elem->Attr(buzz::QN_NAME));
      candidate.set_address(addr);
      candidates->push_back(candidate);
    }
  }
  return true;
}
