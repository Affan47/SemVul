_gnutls_send_client_hello (gnutls_session_t session, int again)
{
  opaque *data = NULL;
  int extdatalen;
  int pos = 0;
  int datalen = 0, ret = 0;
  opaque rnd[TLS_RANDOM_SIZE];
  gnutls_protocol_t hver;
  opaque extdata[MAX_EXT_DATA_LENGTH];

  opaque *SessionID =
    session->internals.resumed_security_parameters.session_id;
  uint8_t session_id_len =
    session->internals.resumed_security_parameters.session_id_size;

  if (SessionID == NULL)
    session_id_len = 0;
  else if (session_id_len == 0)
    SessionID = NULL;

  if (again == 0)
    {

      datalen = 2 + (session_id_len + 1) + TLS_RANDOM_SIZE;


      data = gnutls_malloc (datalen);
      if (data == NULL)
	{
	  gnutls_assert ();
	  return GNUTLS_E_MEMORY_ERROR;
	}


      if (SessionID == NULL)
	hver = _gnutls_version_max (session);
      else
	{
	  hver = session->internals.resumed_security_parameters.version;
	}

      if (hver == GNUTLS_VERSION_UNKNOWN || hver == 0)
	{
	  gnutls_assert ();
	  gnutls_free (data);
	  return GNUTLS_E_INTERNAL_ERROR;
	}

      data[pos++] = _gnutls_version_get_major (hver);
      data[pos++] = _gnutls_version_get_minor (hver);


      _gnutls_set_adv_version (session, hver);


      _gnutls_set_current_version (session, hver);


      session->security_parameters.timestamp = time (NULL);


      _gnutls_tls_create_random (rnd);
      _gnutls_set_client_random (session, rnd);

      memcpy (&data[pos], rnd, TLS_RANDOM_SIZE);
      pos += TLS_RANDOM_SIZE;


      data[pos++] = session_id_len;

      if (session_id_len > 0)
	{
	  memcpy (&data[pos], SessionID, session_id_len);
	  pos += session_id_len;
	}


      extdatalen =
	_gnutls_copy_ciphersuites (session, extdata, sizeof (extdata));
      if (extdatalen > 0)
	{
	  datalen += extdatalen;
	  data = gnutls_realloc_fast (data, datalen);
	  if (data == NULL)
	    {
	      gnutls_assert ();
	      return GNUTLS_E_MEMORY_ERROR;
	    }

	  memcpy (&data[pos], extdata, extdatalen);
	  pos += extdatalen;

	}
      else
	{
	  if (extdatalen == 0)
	    extdatalen = GNUTLS_E_INTERNAL_ERROR;
	  gnutls_free (data);
	  gnutls_assert ();
	  return extdatalen;
	}


      extdatalen =
	_gnutls_copy_comp_methods (session, extdata, sizeof (extdata));
      if (extdatalen > 0)
	{
	  datalen += extdatalen;
	  data = gnutls_realloc_fast (data, datalen);
	  if (data == NULL)
	    {
	      gnutls_assert ();
	      return GNUTLS_E_MEMORY_ERROR;
	    }

	  memcpy (&data[pos], extdata, extdatalen);
	  pos += extdatalen;

	}
      else
	{
	  if (extdatalen == 0)
	    extdatalen = GNUTLS_E_INTERNAL_ERROR;
	  gnutls_free (data);
	  gnutls_assert ();
	  return extdatalen;
	}


      if (hver >= GNUTLS_TLS1)
	{
	  extdatalen =
	    _gnutls_gen_extensions (session, extdata, sizeof (extdata));

	  if (extdatalen > 0)
	    {
	      datalen += extdatalen;
	      data = gnutls_realloc_fast (data, datalen);
	      if (data == NULL)
		{
		  gnutls_assert ();
		  return GNUTLS_E_MEMORY_ERROR;
		}

	      memcpy (&data[pos], extdata, extdatalen);
	    }
	  else if (extdatalen < 0)
	    {
	      gnutls_assert ();
	      gnutls_free (data);
	      return extdatalen;
	    }
	}
    }

  ret =
    _gnutls_send_handshake (session, data, datalen,
			    GNUTLS_HANDSHAKE_CLIENT_HELLO);
  gnutls_free (data);

  return ret;
}
