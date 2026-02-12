build_equiv_class (bitset_t sbcset, const unsigned char *name)
#endif
{
#ifdef _LIBC
  uint32_t nrules = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES);
  if (nrules != 0)
    {
      const int32_t *table, *indirect;
      const unsigned char *weights, *extra, *cp;
      unsigned char char_buf[2];
      int32_t idx1, idx2;
      unsigned int ch;
      size_t len;

      cp = name;
      table = (const int32_t *) _NL_CURRENT (LC_COLLATE, _NL_COLLATE_TABLEMB);
      weights = (const unsigned char *) _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_WEIGHTMB);
      extra = (const unsigned char *) _NL_CURRENT (LC_COLLATE,
						   _NL_COLLATE_EXTRAMB);
      indirect = (const int32_t *) _NL_CURRENT (LC_COLLATE,
						_NL_COLLATE_INDIRECTMB);
      idx1 = findidx (table, indirect, extra, &cp, -1);
      if (BE (idx1 == 0 || *cp != '\0', 0))

	return REG_ECOLLATE;


      len = weights[idx1 & 0xffffff];
      for (ch = 0; ch < SBC_MAX; ++ch)
	{
	  char_buf[0] = ch;
	  cp = char_buf;
	  idx2 = findidx (table, indirect, extra, &cp, 1);


	  if (idx2 == 0)

	    continue;


	  if (len == weights[idx2 & 0xffffff] && (idx1 >> 24) == (idx2 >> 24))
	    {
	      int cnt = 0;

	      while (cnt <= len &&
		     weights[(idx1 & 0xffffff) + 1 + cnt]
		     == weights[(idx2 & 0xffffff) + 1 + cnt])
		++cnt;

	      if (cnt > len)
		bitset_set (sbcset, ch);
	    }
	}

      if (BE (*equiv_class_alloc == mbcset->nequiv_classes, 0))
	{


	  Idx new_equiv_class_alloc = 2 * mbcset->nequiv_classes + 1;

	  int32_t *new_equiv_classes = re_realloc (mbcset->equiv_classes,
						   int32_t,
						   new_equiv_class_alloc);
	  if (BE (new_equiv_classes == NULL, 0))
	    return REG_ESPACE;
	  mbcset->equiv_classes = new_equiv_classes;
	  *equiv_class_alloc = new_equiv_class_alloc;
	}
      mbcset->equiv_classes[mbcset->nequiv_classes++] = idx1;
    }
  else
#endif
    {
      if (BE (strlen ((const char *) name) != 1, 0))
	return REG_ECOLLATE;
      bitset_set (sbcset, *name);
    }
  return REG_NOERROR;
}
