log_get_file(const char *subsys)
{
  struct LogDesc *desc;


  if (!(desc = log_find(subsys)))
    return 0;

  return desc->file ? desc->file->file : 0;
}
