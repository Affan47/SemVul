SSLNetVConnection::read_raw_data()
{

  int64_t r          = 0;
  int64_t total_read = 0;
  int64_t rattempted = 0;
  char *buffer       = nullptr;
  int buf_len;
  IOBufferBlock *b = this->handShakeBuffer->first_write_block();

  rattempted = b->write_avail();
  while (rattempted) {
    buffer  = b->_end;
    buf_len = rattempted;
    b       = b->next.get();

    r = socketManager.read(this->con.fd, buffer, buf_len);
    NET_INCREMENT_DYN_STAT(net_calls_to_read_stat);
    total_read += rattempted;


    if (r != rattempted || !b) {
      break;
    }

    rattempted = b->write_avail();
  }


  if (r != rattempted) {

    if (r <= 0 && total_read > rattempted) {
      r = total_read - rattempted;
    } else {
      r = total_read - rattempted + r;
    }
  }
  NET_SUM_DYN_STAT(net_read_bytes_stat, r);

  IpMap *pp_ipmap;
  pp_ipmap = SSLConfigParams::proxy_protocol_ipmap;

  if (this->get_is_proxy_protocol()) {
    Debug("proxyprotocol", "[SSLNetVConnection::read_raw_data] proxy protocol is enabled on this port");
    if (pp_ipmap->getCount() > 0) {
      Debug("proxyprotocol",
            "[SSLNetVConnection::read_raw_data] proxy protocol has a configured whitelist of trusted IPs - checking");


      void *payload = nullptr;
      if (!pp_ipmap->contains(get_remote_addr(), &payload)) {
        Debug("proxyprotocol",
              "[SSLNetVConnection::read_raw_data] proxy protocol src IP is NOT in the configured whitelist of trusted IPs - "
              "closing connection");
        r = -ENOTCONN;
        goto proxy_protocol_bypass;
      } else {
        char new_host[INET6_ADDRSTRLEN];
        Debug("proxyprotocol", "[SSLNetVConnection::read_raw_data] Source IP [%s] is in the trusted whitelist for proxy protocol",
              ats_ip_ntop(this->get_remote_addr(), new_host, sizeof(new_host)));
      }
    } else {
      Debug("proxyprotocol",
            "[SSLNetVConnection::read_raw_data] proxy protocol DOES NOT have a configured whitelist of trusted IPs but "
            "proxy protocol is ernabled on this port - processing all connections");
    }

    if (ssl_has_proxy_v1(this, buffer, &r)) {
      Debug("proxyprotocol", "[SSLNetVConnection::read_raw_data] ssl has proxy_v1 header");
      set_remote_addr(get_proxy_protocol_src_addr());
    } else {
      Debug("proxyprotocol",
            "[SSLNetVConnection::read_raw_data] proxy protocol was enabled, but required header was not present in the "
            "transaction - closing connection");
    }
  }

proxy_protocol_bypass:

  if (r > 0) {
    this->handShakeBuffer->fill(r);

    char *start              = this->handShakeReader->start();
    char *end                = this->handShakeReader->end();
    this->handShakeBioStored = end - start;


    BIO *rbio = BIO_new_mem_buf(start, this->handShakeBioStored);
    BIO_set_mem_eof_return(rbio, -1);
    SSL_set0_rbio(this->ssl, rbio);
  } else {
    this->handShakeBioStored = 0;
  }

  Debug("ssl", "%p read r=%" PRId64 " total=%" PRId64 " bio=%d\n", this, r, total_read, this->handShakeBioStored);


  if (r <= 0) {
    if (r == -EAGAIN || r == -ENOTCONN) {
      NET_INCREMENT_DYN_STAT(net_calls_to_read_nodata_stat);
    }
  }

  return r;
}
