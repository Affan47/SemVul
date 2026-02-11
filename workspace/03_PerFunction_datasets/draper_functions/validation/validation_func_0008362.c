task_kill_running(struct task_pak *task)
{
gint i;
struct task_pak *process;


if (task && psarray)
  {
  for (i=psarray->len ; i-- ; )
    {
    process = &g_array_index(psarray, struct task_pak, i);
    if (process->pid == task->pid)
      {
      task_kill_tree(process->child);
      break;
      }
    }
  task->status = KILLED;
  }
}
