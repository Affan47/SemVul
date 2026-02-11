wire_expmem()
{
  wire_list *w = wirelist;
  int size = 0;

  while (w) {
    size += sizeof(wire_list);
    size += strlen(w->crypt) + 1;
    size += strlen(w->key) + 1;
    w = w->next;
  }
  return size;
}
