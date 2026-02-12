int fake_tm_init(

  void             *info,
  struct  tm_roots *roots)

  {
  tm_event_t  nevent, revent;


  int   nerr = 0;


  init_done = 1;

  nevent = new_event();

  add_event(nevent, TM_ERROR_NODE, TM_INIT, (void *)roots);
  tm_poll(TM_NULL_EVENT, &revent, 1, &nerr);
  return(0);
  }
