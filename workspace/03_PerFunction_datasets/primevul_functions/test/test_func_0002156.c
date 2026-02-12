static SLJIT_INLINE void set_jumps(jump_list *list, struct sljit_label *label)
{
while (list)
  {


  SET_LABEL(list->jump, label);
  list = list->next;
  }
}
