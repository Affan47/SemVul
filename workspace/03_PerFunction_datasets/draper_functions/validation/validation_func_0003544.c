nxt_set_name(nxt_t *nxt,char *name) {
  nxt_pack_start(nxt,0x98);
  nxt_pack_str(nxt,name,15);
  test(nxt_con_send(nxt));
  test(nxt_con_recv(nxt,3));
  test(nxt_unpack_start(nxt,0x98));
  if (nxt_unpack_error(nxt)==0) {
    free(nxt->name);
    nxt->name = strdup(name);
    return NXT_SUCC;
  }
  else return NXT_FAIL;
}
