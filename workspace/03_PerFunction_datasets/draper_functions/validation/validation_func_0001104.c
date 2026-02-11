_gftpui_gtk_thread_func (void *data)
{
  gftpui_gtk_thread_data * thread_data;
  void *ret;

  thread_data = data;
  ret = thread_data->func (thread_data->cdata);

  if (thread_data->cdata->request->wakeup_main_thread[1] > 0)
    write (thread_data->cdata->request->wakeup_main_thread[1], " ", 1);

  return (ret);
}
