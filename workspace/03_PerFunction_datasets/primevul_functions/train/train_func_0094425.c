SSLNetVConnection::update_rbio(bool move_to_socket)
{
  bool retval = false;
  if (BIO_eof(SSL_get_rbio(this->ssl))) {
    this->handShakeReader->consume(this->handShakeBioStored);
    this->handShakeBioStored = 0;

    if (this->handShakeReader->is_read_avail_more_than(0)) {

      char *start              = this->handShakeReader->start();
      char *end                = this->handShakeReader->end();
      this->handShakeBioStored = end - start;


      BIO *rbio = BIO_new_mem_buf(start, this->handShakeBioStored);
      BIO_set_mem_eof_return(rbio, -1);
      SSL_set0_rbio(this->ssl, rbio);
      retval = true;

    } else if (move_to_socket && this->handShakeHolder->is_read_avail_more_than(0)) {
      BIO *rbio = BIO_new_fd(this->get_socket(), BIO_NOCLOSE);
      BIO_set_mem_eof_return(rbio, -1);
      SSL_set0_rbio(this->ssl, rbio);
      free_handshake_buffers();
    }
  }
  return retval;
}
