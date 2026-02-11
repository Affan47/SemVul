find_one_section (void *data, const char *name, off_t offset, off_t length)
{
  struct find_one_section_data *fosd = (struct find_one_section_data *) data;

  if (strcmp (name, fosd->name) != 0)
    return 1;

  *fosd->offset = offset;
  *fosd->length = length;
  fosd->found = 1;


  return 0;
}
