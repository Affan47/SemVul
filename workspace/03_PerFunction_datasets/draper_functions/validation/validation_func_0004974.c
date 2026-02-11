info_get_labeled_reference (char *label, REFERENCE **references)
{
  register int i;
  REFERENCE *entry;

  for (i = 0; references && (entry = references[i]); i++)
    {
      if (strcmp (label, entry->label) == 0)
        return entry;
    }
  return NULL;
}
