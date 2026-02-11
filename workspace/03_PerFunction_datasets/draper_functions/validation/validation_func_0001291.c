prio_insert(Prio_list node, Prio_list list, Boolean desc)
{
  Prio_list p;


  if (first(list) == nil(list) ||
      (!desc && first(list)->prio >= node->prio) ||
      (desc  && first(list)->prio <= node->prio) ) {
    node->blink = list;
    node->flink = list->flink;
    list->flink->blink = node;
    list->flink = node;
    return;
  }

  if ((desc  && last(list)->prio >= node->prio) ||
      (!desc && last(list)->prio <= node->prio) ) {
    node->flink = list;
    node->blink = list->blink;
    list->blink->flink = node;
    list->blink = node;
    return;
  }

  for(p = next(first(list));  ; p = next(p)) {
    if (p == nil(list)) fprintf(stderr, "inserting into tail did not work\n");
    if ((!desc && p->prio >= node->prio) ||
        (desc  && p->prio <= node->prio)) {
      node->flink = p;
      node->blink = p->blink;
      p->blink->flink = node;
      p->blink = node;
      return;
    }
  }
}
