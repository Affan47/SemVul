matsushita_build_paper_sizes (Matsushita_Scanner * dev)
{
  SANE_String_Const *psl;
  int *psv;
  int num;
  int i;

  DBG (DBG_proc, "matsushita_build_paper_sizes: enter\n");

  psl = malloc ((sizeof (SANE_String_Const) + 1) * NELEMS (paper_sizes));
  if (psl == NULL)
    {
      DBG (DBG_error, "ERROR: not enough memory\n");
      return SANE_STATUS_NO_MEM;
    }

  psv = malloc ((sizeof (int) + 1) * NELEMS (paper_sizes));
  if (psv == NULL)
    {
      DBG (DBG_error, "ERROR: not enough memory\n");
      free (psl);
      return SANE_STATUS_NO_MEM;
    }

  for (i = 0, num = 0; i < NELEMS (paper_sizes); i++)
    {
      if (SANE_UNFIX (scanners[dev->scnum].x_range.max) >=
	  paper_sizes[i].width
	  && SANE_UNFIX (scanners[dev->scnum].y_range.max) >=
	  paper_sizes[i].length)
	{


	  psl[num] = paper_sizes[i].name;
	  psv[num] = i;
	  num++;
	}
    }
  psl[num] = NULL;

  dev->paper_sizes_list = psl;
  dev->paper_sizes_val = psv;

  DBG (DBG_proc, "matsushita_build_paper_sizes: exit (%d)\n", num);

  return SANE_STATUS_GOOD;
}
