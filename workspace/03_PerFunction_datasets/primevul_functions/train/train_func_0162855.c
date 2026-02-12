static int malformed_pgp_encrypted_handler (BODY *b, STATE *s)
{
  int rc;
  BODY *octetstream;

  octetstream = b->parts->next->next;


  mutt_free_envelope (&b->mime_headers);
  mutt_free_envelope (&octetstream->mime_headers);


  rc = run_decode_and_handler (octetstream, s, crypt_pgp_encrypted_handler, 0);
  b->goodsig |= octetstream->goodsig;
#ifdef USE_AUTOCRYPT
  b->is_autocrypt |= octetstream->is_autocrypt;
#endif


  if (!rc && octetstream->mime_headers)
  {
    b->mime_headers = octetstream->mime_headers;
    octetstream->mime_headers = NULL;
  }

  return rc;
}
