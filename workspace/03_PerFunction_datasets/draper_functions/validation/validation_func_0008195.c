gp_archive_list_members(gp_archive_type *archive)
{
  const char *format = "%-24s  %06i bytes  %s";
  char name[256];
  char *end;
  int date;
  time_t time;
  int size;


  if (gp_archive_have_index(archive))
    archive = archive->next;

  while (archive != NULL) {
    sscanf(archive->header.ar_name, "%255s/", name);
    sscanf(archive->header.ar_date, "%il", &date);
    sscanf(archive->header.ar_size, "%il", &size);
    end = strchr(&name[0], '/');
    if (end != NULL)
      *end = '\0';
    time = date;
    printf(format, name, size, ctime(&time));
    archive = archive->next;
  }

  return;
}
