process(PayloadRawInterface *request,
                                PayloadStreamInterface **response, bool tls) {
    *response = NULL;
    MCC_Status r;
    if (!(r=Load())) return r;
    if ((tls && !tls_entry) || (!tls && !tcp_entry)) {
      return MCC_Status(GENERIC_ERROR,"COMMUNICATION","MCC chain loading produced no entry point");
    }
    MessageAttributes attributes_req;
    MessageAttributes attributes_rep;
    Message reqmsg;
    Message repmsg;
    reqmsg.Attributes(&attributes_req);
    reqmsg.Context(&context);
    reqmsg.Payload(request);
    repmsg.Attributes(&attributes_rep);
    repmsg.Context(&context);

    if (tls) {
      r = tls_entry->process(reqmsg, repmsg);
    } else {
      r = tcp_entry->process(reqmsg, repmsg);
    }

    if (repmsg.Payload() != NULL) {
      try {
        *response =
          dynamic_cast<PayloadStreamInterface*>(repmsg.Payload());
      } catch (std::exception&) {
        delete repmsg.Payload();
      }
    }
    return r;
  }
