change_param(const String &in_s, Element *e, void *vparam,
			     ErrorHandler *errh)
{
  InfiniteSource *is = (InfiniteSource *)e;
  String s = cp_uncomment(in_s);
  switch ((intptr_t)vparam) {

   case 0: {
     String data;
     if (!cp_string(s, &data))
       return errh->error("data parameter must be string");
     is->_data = data;
     is->setup_packet();
     break;
   }

   case 1: {
     int limit;
     if (!cp_integer(s, &limit))
       return errh->error("limit parameter must be integer");
     is->_limit = limit;
     break;
   }

   case 2: {
     int burstsize;
     if (!cp_integer(s, &burstsize) || burstsize < 1)
       return errh->error("burstsize parameter must be integer >= 1");
     is->_burstsize = burstsize;
     break;
   }

   case 3: {
     bool active;
     if (!cp_bool(s, &active))
       return errh->error("active parameter must be boolean");
     is->_active = active;
     break;
   }

   case 5: {
     is->_count = 0;
     break;
   }

   case 6: {
     int datasize;
     if (!cp_integer(s, &datasize) || datasize < 1)
       return errh->error("datasize parameter must be integer >= 1");
     is->_datasize = datasize;
     is->setup_packet();
     break;
   }
  }

  if (is->_active && (is->_limit < 0 || is->_count < is->_limit)) {
    if (is->output_is_push(0) && !is->_task.scheduled())
      is->_task.reschedule();

    if (is->output_is_pull(0) && !is->Notifier::active())
      is->wake();
  }
  return 0;
}
