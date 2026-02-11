spawnrender (gpointer data,
                         gpointer foo)
{
  ThreadData *td = data;
  GeglBuffer * buffer;
  buffer = gegl_node_apply_roi (td->node, td->pad, &td->roi, td->tid);

  if ((buffer ) && td->destination_buf)
    {
      gegl_buffer_get (buffer, &td->roi, 1.0, td->format, td->destination_buf, td->rowstride,
                       GEGL_ABYSS_NONE);
    }


  if (buffer)
    g_object_unref (buffer);

  g_mutex_lock (mutex);
  remaining_tasks --;
  if (remaining_tasks == 0)
    {

      g_cond_signal (cond);
    }
  g_mutex_unlock (mutex);
}
