child_setup (gpointer user_data)
{
  GArray *fd_array = user_data;
  int i;


  if (fd_array == NULL)
    return;


  for (i = 0; i < fd_array->len; i++)
    fcntl (g_array_index (fd_array, int, i), F_SETFD, 0);
}
