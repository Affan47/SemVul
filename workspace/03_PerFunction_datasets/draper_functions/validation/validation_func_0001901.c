Empty()
{
  if(rq_head) _empty_slice_list(&rq_head);
  rq_send = rq_head;
}
