static void langmap_init(void)
{
  for (int i = 0; i < 256; i++)
    langmap_mapchar[i] = (char_u)i;
  ga_init(&langmap_mapga, sizeof(langmap_entry_T), 8);
}
