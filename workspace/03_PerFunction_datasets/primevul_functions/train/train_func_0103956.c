ospf_make_md5_digest (struct ospf_interface *oi, struct ospf_packet *op)
{
  struct ospf_header *ospfh;
  unsigned char digest[OSPF_AUTH_MD5_SIZE];
  MD5_CTX ctx;
  void *ibuf;
  u_int32_t t;
  struct crypt_key *ck;
  const u_int8_t *auth_key;

  ibuf = STREAM_DATA (op->s);
  ospfh = (struct ospf_header *) ibuf;

  if (ntohs (ospfh->auth_type) != OSPF_AUTH_CRYPTOGRAPHIC)
    return 0;


  t = (time(NULL) & 0xFFFFFFFF);
  if (t > oi->crypt_seqnum)
    oi->crypt_seqnum = t;
  else
    oi->crypt_seqnum++;

  ospfh->u.crypt.crypt_seqnum = htonl (oi->crypt_seqnum);


  if (list_isempty (OSPF_IF_PARAM (oi, auth_crypt)))
    auth_key = (const u_int8_t *) "";
  else
    {
      ck = listgetdata (listtail(OSPF_IF_PARAM (oi, auth_crypt)));
      auth_key = ck->auth_key;
    }


  memset(&ctx, 0, sizeof(ctx));
  MD5Init(&ctx);
  MD5Update(&ctx, ibuf, ntohs (ospfh->length));
  MD5Update(&ctx, auth_key, OSPF_AUTH_MD5_SIZE);
  MD5Final(digest, &ctx);


  stream_put (op->s, digest, OSPF_AUTH_MD5_SIZE);


  op->length = ntohs (ospfh->length) + OSPF_AUTH_MD5_SIZE;

  if (stream_get_endp(op->s) != op->length)

    zlog_warn("ospf_make_md5_digest: length mismatch stream %lu ospf_packet %u",
	      (u_long)stream_get_endp(op->s), op->length);

  return OSPF_AUTH_MD5_SIZE;
}
