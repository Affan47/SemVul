copy_record_version (gnutls_session_t session,
                     gnutls_handshake_description_t htype, opaque version[2])
{
  gnutls_protocol_t lver;

  if (session->internals.initial_negotiation_completed || htype != GNUTLS_HANDSHAKE_CLIENT_HELLO
      || session->internals.default_record_version[0] == 0)
    {
      lver = gnutls_protocol_get_version (session);

      version[0] = _gnutls_version_get_major (lver);
      version[1] = _gnutls_version_get_minor (lver);
    }
  else
    {
      version[0] = session->internals.default_record_version[0];
      version[1] = session->internals.default_record_version[1];
    }
}
