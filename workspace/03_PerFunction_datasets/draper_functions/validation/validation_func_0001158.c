gnutls_openpgp_privkey_get_subkey_id (gnutls_openpgp_privkey_t key,
                                      unsigned int idx,
                                      gnutls_openpgp_keyid_t keyid)
{
  cdk_packet_t pkt;
  uint32_t kid[2];

  if (!key || !keyid)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  pkt = _get_secret_subkey (key, idx);
  if (!pkt)
    return GNUTLS_E_OPENPGP_GETKEY_FAILED;

  cdk_sk_get_keyid (pkt->pkt.secret_key, kid);
  _gnutls_write_uint32 (kid[0], keyid);
  _gnutls_write_uint32 (kid[1], keyid + 4);

  return 0;
}
