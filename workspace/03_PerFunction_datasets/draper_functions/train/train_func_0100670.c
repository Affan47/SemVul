get_chars_for_script (const gchar            *script,
                      UnicodeRange          **ranges,
                      gint                   *size)
{
  gint i, j, index;
  gint script_index, common_script_index;
  gint prev_end;

  script_index = find_script (script);
  common_script_index = find_script ("Common");
  if (script_index == -1)
    return FALSE;

  j = 0;

  if (script_index == common_script_index)
    {
      prev_end = -1;
      for (i = 0;  i < G_N_ELEMENTS (unicode_scripts);  i++)
	{
	  if (unicode_scripts[i].start > prev_end + 1)
	    j++;
	  prev_end = unicode_scripts[i].end;
	}
      if (unicode_scripts[i-1].end < UNICHAR_MAX)
	j++;
    }

  for (i = 0;  i < G_N_ELEMENTS (unicode_scripts);  i++)
    if (unicode_scripts[i].script_index == script_index)
      j++;

  *size = j;
  *ranges = g_new (UnicodeRange, *size);

  j = 0, index = 0, prev_end = -1;

  for (i = 0;  i < G_N_ELEMENTS (unicode_scripts);  i++)
    {
      if (script_index == common_script_index)
	{
	  if (unicode_scripts[i].start > prev_end + 1)
	    {
	      (*ranges)[j].start = prev_end + 1;
	      (*ranges)[j].end = unicode_scripts[i].start - 1;
	      (*ranges)[j].index = index;

	      index += (*ranges)[j].end - (*ranges)[j].start + 1;
	      j++;
	    }

	  prev_end = unicode_scripts[i].end;
	}

      if (unicode_scripts[i].script_index == script_index)
	{
	  (*ranges)[j].start = unicode_scripts[i].start;
	  (*ranges)[j].end = unicode_scripts[i].end;
	  (*ranges)[j].index = index;

	  index += (*ranges)[j].end - (*ranges)[j].start + 1;
	  j++;
	}
    }

  if (script_index == common_script_index)
    {
      if (unicode_scripts[i-1].end < UNICHAR_MAX)
	{
	  (*ranges)[j].start = unicode_scripts[i-1].end + 1;
	  (*ranges)[j].end = UNICHAR_MAX;
	  (*ranges)[j].index = index;
	  j++;
	}
    }


  g_assert (j == *size);

  return TRUE;
}
