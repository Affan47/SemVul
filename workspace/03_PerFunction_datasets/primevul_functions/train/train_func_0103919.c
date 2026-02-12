ospf_make_ls_upd (struct ospf_interface *oi, struct list *update, struct stream *s)
{
  struct ospf_lsa *lsa;
  struct listnode *node;
  u_int16_t length = 0;
  unsigned int size_noauth;
  unsigned long delta = stream_get_endp (s);
  unsigned long pp;
  int count = 0;

  if (IS_DEBUG_OSPF_EVENT)
    zlog_debug ("ospf_make_ls_upd: Start");

  pp = stream_get_endp (s);
  stream_forward_endp (s, OSPF_LS_UPD_MIN_SIZE);
  length += OSPF_LS_UPD_MIN_SIZE;


  size_noauth = stream_get_size(s) - ospf_packet_authspace(oi);

  while ((node = listhead (update)) != NULL)
    {
      struct lsa_header *lsah;
      u_int16_t ls_age;

      if (IS_DEBUG_OSPF_EVENT)
        zlog_debug ("ospf_make_ls_upd: List Iteration");

      lsa = listgetdata (node);

      assert (lsa->data);


      if (length + delta + ntohs (lsa->data->length) > size_noauth)
        break;


      lsah = (struct lsa_header *) (STREAM_DATA (s) + stream_get_endp (s));


      stream_put (s, lsa->data, ntohs (lsa->data->length));


      ls_age = ls_age_increment (lsa, OSPF_IF_PARAM (oi, transmit_delay));
      lsah->ls_age = htons (ls_age);

      length += ntohs (lsa->data->length);
      count++;

      list_delete_node (update, node);
      ospf_lsa_unlock (&lsa);
    }


  stream_putl_at (s, pp, count);

  if (IS_DEBUG_OSPF_EVENT)
    zlog_debug ("ospf_make_ls_upd: Stop");
  return length;
}
