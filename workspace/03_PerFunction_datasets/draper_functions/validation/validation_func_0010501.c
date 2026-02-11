cmd_me(struct userrec *u, int idx, char *par)
{
  int i;

  if (dcc[idx].u.chat->channel < 0) {
    dprintf(idx, "You have chat turned off.\n");
    return;
  }
  if (!par[0]) {
    dprintf(idx, "Usage: me <action>\n");
    return;
  }
  if (dcc[idx].u.chat->away != NULL)
    not_away(idx);
  for (i = 0; i < dcc_total; i++)
    if ((dcc[i].type->flags & DCT_CHAT) &&
        (dcc[i].u.chat->channel == dcc[idx].u.chat->channel) &&
        ((i != idx) || (dcc[i].status & STAT_ECHO)))
      dprintf(i, "* %s %s\n", dcc[idx].nick, par);
  botnet_send_act(idx, botnetnick, dcc[idx].nick,
                  dcc[idx].u.chat->channel, par);
  check_tcl_act(dcc[idx].nick, dcc[idx].u.chat->channel, par);
}
