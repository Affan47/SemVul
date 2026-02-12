ospf_packet_dup (struct ospf_packet *op)
{
  struct ospf_packet *new;

  if (stream_get_endp(op->s) != op->length)

    zlog_warn ("ospf_packet_dup stream %lu ospf_packet %u size mismatch",
	       (u_long)STREAM_SIZE(op->s), op->length);


  new = ospf_packet_new (stream_get_endp(op->s) + OSPF_AUTH_MD5_SIZE);
  stream_copy (new->s, op->s);

  new->dst = op->dst;
  new->length = op->length;

  return new;
}
