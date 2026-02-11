_gnutls_record_buffer_put (content_type_t type,
                           gnutls_session_t session, opaque * data,
                           size_t length)
{
  gnutls_buffer_st *buf;

  if (length == 0)
    return 0;

  switch (type)
    {
    case GNUTLS_APPLICATION_DATA:
      buf = &session->internals.application_data_buffer;
      _gnutls_buffers_log ("BUF[REC]: Inserted %d bytes of Data(%d)\n",
                           (int) length, (int) type);
      break;

    case GNUTLS_HANDSHAKE:
      buf = &session->internals.handshake_data_buffer;
      _gnutls_buffers_log ("BUF[HSK]: Inserted %d bytes of Data(%d)\n",
                           (int) length, (int) type);
      break;

    case GNUTLS_INNER_APPLICATION:
      buf = &session->internals.ia_data_buffer;
      _gnutls_buffers_log ("BUF[IA]: Inserted %d bytes of Data(%d)\n",
                           (int) length, (int) type);
      break;

    default:
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  if (_gnutls_buffer_append_data (buf, data, length) < 0)
    {
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  return 0;
}
