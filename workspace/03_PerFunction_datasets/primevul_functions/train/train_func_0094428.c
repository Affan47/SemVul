SSLNetVConnection::populate(Connection &con, Continuation *c, void *arg)
{
  int retval = super::populate(con, c, arg);
  if (retval != EVENT_DONE) {
    return retval;
  }

  this->ssl = (SSL *)arg;


  this->sslHandShakeComplete = true;
  SSLNetVCAttach(this->ssl, this);
  return EVENT_DONE;
}
