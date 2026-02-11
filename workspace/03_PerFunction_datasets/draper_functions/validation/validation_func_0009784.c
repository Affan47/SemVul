pop_back_seg_ent(struct anthy_context *c)
{
  struct seg_ent *s;
  s = c->seg_list.list_head.prev;
  if (s == &c->seg_list.list_head) {
    return ;
  }
  s->prev->next = s->next;
  s->next->prev = s->prev;
  release_segment(s);
  c->seg_list.nr_segments --;
}
