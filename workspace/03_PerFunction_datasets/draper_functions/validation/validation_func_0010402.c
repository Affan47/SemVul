compare_names(const ppd_info_t *p0,
              const ppd_info_t *p1)
{
  int	diff;


  if ((diff = strcmp(p0->record.filename, p1->record.filename)) != 0)
    return (diff);
  else
    return (strcmp(p0->record.name, p1->record.name));
}
