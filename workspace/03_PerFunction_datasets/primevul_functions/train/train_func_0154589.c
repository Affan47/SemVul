langmap_init(void)
{
    int i;

    for (i = 0; i < 256; i++)
	langmap_mapchar[i] = i;
# ifdef FEAT_MBYTE
    ga_init2(&langmap_mapga, sizeof(langmap_entry_T), 8);
# endif
}
