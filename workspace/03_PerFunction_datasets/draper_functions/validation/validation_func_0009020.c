matewnck_task_queue_glow (MatewnckTask *task)
{
  if (task->button_glow == 0)
    {
      task->glow_start_time = 0.0;


      task->button_glow =
        g_timeout_add_full (G_PRIORITY_DEFAULT_IDLE,
                            50,
                            (GSourceFunc) matewnck_task_button_glow, task,
                            (GDestroyNotify) matewnck_task_clear_glow_start_timeout_id);
    }
}
