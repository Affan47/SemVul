CmdListRemoveFromList(XOTclCmdList **cmdList, XOTclCmdList *delCL) {
  register XOTclCmdList *c = *cmdList, *del = NULL;
  if (c == NULL)
    return NULL;
  if (c == delCL) {
    *cmdList = c->next;
    del = c;
  } else {
    while (c->next && c->next != delCL) {
      c = c->next;
    }
    if (c->next == delCL) {
      del = delCL;
      c->next = delCL->next;
    }
  }
  return del;
}
