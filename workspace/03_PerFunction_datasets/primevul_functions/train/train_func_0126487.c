same_hosts(host_item *one, host_item *two)
{
while (one && two)
  {
  if (Ustrcmp(one->name, two->name) != 0)
    {
    int mx = one->mx;
    host_item *end_one = one;
    host_item *end_two = two;


    if (mx == MX_NONE) return FALSE;


    while (  end_one->next && end_one->next->mx == mx
          && end_two->next && end_two->next->mx == mx)
      {
      end_one = end_one->next;
      end_two = end_two->next;
      }


    if (end_one == one) return FALSE;


    for (;;)
      {
      host_item *hi;
      for (hi = two; hi != end_two->next; hi = hi->next)
        if (Ustrcmp(one->name, hi->name) == 0) break;
      if (hi == end_two->next) return FALSE;
      if (one == end_one) break;
      one = one->next;
      }


    two = end_two;
    }


  else if (one->port != two->port)
    return FALSE;


  one = one->next;
  two = two->next;
  }


return (one == two);
}
