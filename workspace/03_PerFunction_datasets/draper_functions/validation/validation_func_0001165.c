initialize(ErrorHandler *errh)
{
  _count = 0;
  if (output_is_push(0))
    ScheduleInfo::initialize_task(this, &_task, errh);
  return 0;
}
