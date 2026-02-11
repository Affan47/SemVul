timevar_push (timevar_id_t timevar)
{
  struct timevar_def *tv = &timevars[timevar];
  struct timevar_stack_def *context;
  struct timevar_time_def now;

  if (!timevar_enable)
    return;


  tv->used = 1;


  if (tv->standalone)
    abort ();


  get_time (&now);


  if (stack)
    timevar_accumulate (&stack->timevar->elapsed, &start_time, &now);


  start_time = now;


  if (unused_stack_instances != NULL)
    {
      context = unused_stack_instances;
      unused_stack_instances = unused_stack_instances->next;
    }
  else
    context = xmalloc (sizeof (struct timevar_stack_def));


  context->timevar = tv;
  context->next = stack;
  stack = context;
}
