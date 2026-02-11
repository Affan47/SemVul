task_process(struct task_pak *task, gpointer data)
{

if (!task)
  return;
if (task->status != QUEUED)
  return;


task->pid = getpid();

task->status = RUNNING;


task->primary(task->ptr1, task);


gdk_threads_enter();

if (task->status != KILLED)
  {

  if (task->cleanup)
    task->cleanup(task->ptr2);
  task->status = COMPLETED;
  }

gdk_flush();
gdk_threads_leave();


gdk_beep();
}
