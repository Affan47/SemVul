imCounterSetCallback(void* user_data, imCounterCallback counter_func)
{
  imCounterCallback old_counter_func = iCounterFunc;
  iCounterFunc = counter_func;
  if (user_data)
    iCounterUserData = user_data;
  return old_counter_func;
}
