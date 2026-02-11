print_order(String *str,
                                ORDER *order,
                                enum_query_type query_type)
{
  for (; order; order= order->next)
  {
    if (order->counter_used)
    {
      char buffer[20];
      size_t length= my_snprintf(buffer, 20, "%d", order->counter);
      str->append(buffer, (uint) length);
    }
    else
      (*order->item)->print(str, query_type);
    if (!order->asc)
      str->append(STRING_WITH_LEN(" desc"));
    if (order->next)
      str->append(',');
  }
}
