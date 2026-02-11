configLoadTagmap (void)
{
  FILE *fp = fopen_local ("tagmap.ini", "r");

  if (fp) {
    char buf[INI_LINE_BUF_LEN];
    char *key, *val;
    int type;
    int id = -1, id2 = -1;

    while ((type = get_ini_line (fp, buf, &key, &val))) {
      if (type == 1) {
	id++;
	RCOXML_TABLE_TAGS =
	    (RcoTagMap) realloc (RCOXML_TABLE_TAGS,
	    sizeof (*RCOXML_TABLE_TAGS) * (id + 2));
	RCOXML_TABLE_TAGS[id][0][0] = 0;
	id2 = -1;
	RCOXML_TABLE_NAMES =
	    (RcoTableMap) realloc (RCOXML_TABLE_NAMES,
	    sizeof (*RCOXML_TABLE_NAMES) * (id + 1));
	strcpy (RCOXML_TABLE_NAMES[id], key);
      } else {
	if (id == -1)
	  continue;
	id2++;
	if (id2 >= RCO_TAGMAP_SIZE - 2) {
	  error ("Too many types.");
	  exit (1);
	}
	strcpy (RCOXML_TABLE_TAGS[id][id2], key);
	RCOXML_TABLE_TAGS[id][id2 + 1][0] = 0;
      }
    }
    fclose (fp);
    RCOXML_TABLE_TAGS_NUM = id + 1;
  } else {
    error ("Could not open map file.");
    exit (1);
  }
}
