_gnutls_server_name_send_params (gnutls_session_t session,
				 opaque * data, size_t _data_size)
{
  uint16_t len;
  opaque *p;
  unsigned i;
  ssize_t data_size = _data_size;
  int total_size = 0;


  if (session->security_parameters.entity == GNUTLS_CLIENT)
    {

      if (session->security_parameters.extensions.server_names_size == 0)
	return 0;


      total_size = 2;
      for (i = 0;
	   i < session->security_parameters.extensions.server_names_size; i++)
	{


	  len =
	    session->security_parameters.extensions.server_names[i].
	    name_length;


	  total_size += 1 + 2 + len;
	}

      p = data;


      DECR_LENGTH_RET (data_size, 2, GNUTLS_E_SHORT_MEMORY_BUFFER);
      _gnutls_write_uint16 (total_size - 2, p);
      p += 2;

      for (i = 0;
	   i < session->security_parameters.extensions.server_names_size; i++)
	{

	  switch (session->security_parameters.extensions.
		  server_names[i].type)
	    {
	    case GNUTLS_NAME_DNS:

	      len =
		session->security_parameters.extensions.
		server_names[i].name_length;
	      if (len == 0)
		break;


	      DECR_LENGTH_RET (data_size, len + 3,
			       GNUTLS_E_SHORT_MEMORY_BUFFER);

	      *p = 0;
	      p++;

	      _gnutls_write_uint16 (len, p);
	      p += 2;

	      memcpy (p,
		      session->security_parameters.extensions.
		      server_names[i].name, len);
	      p += len;
	      break;
	    default:
	      gnutls_assert ();
	      return GNUTLS_E_INTERNAL_ERROR;
	    }
	}
    }

  return total_size;
}
