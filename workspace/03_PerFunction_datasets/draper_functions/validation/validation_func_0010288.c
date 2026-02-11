interruptWorkerTask (Task *task)
{
  ASSERT(osThreadId() != task->id);
  ASSERT(task->incall->suspended_tso);
  interruptOSThread(task->id);
  debugTrace(DEBUG_sched, "interrupted worker task %p", taskId(task));
}
