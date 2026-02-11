_gcry_random_progress (const char *what, int printchar, int current, int total)
{
  if (progress_cb)
    progress_cb (progress_cb_data, what, printchar, current, total);
}
