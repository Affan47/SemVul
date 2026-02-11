ask_results(struct res_db *db)
{
  struct conv_res *cr;
  for (cr = db->res_list.next; cr; cr = cr->next) {
    if (cr->check == CHK_UNKNOWN && cr->used == 1) {
      char buf[256];
      printf("%s -> %s (y/n/d/q)\n", cr->src_str, cr->res_str);
      fgets(buf, 256, stdin);
      if (buf[0] == 'y') {
	cr->check = CHK_OK;
      } else if (buf[0] == 'n') {
	cr->check = CHK_MISS;
      } else if (buf[0] == 'd') {
	cr->check = CHK_DONTCARE;
      } else if (buf[0] == 'q') {
	return ;
      }
    }
  }
}
