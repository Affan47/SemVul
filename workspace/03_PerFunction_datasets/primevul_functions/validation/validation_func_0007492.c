parse_bracket_exp (re_string_t *regexp, re_dfa_t *dfa, re_token_t *token,
		   reg_syntax_t syntax, reg_errcode_t *err)
{
#ifdef _LIBC
  const unsigned char *collseqmb;
  const char *collseqwc;
  uint32_t nrules;
  int32_t table_size;
  const int32_t *symb_table;
  const unsigned char *extra;


  auto inline int32_t
  __attribute__ ((always_inline))
  seek_collating_symbol_entry (const unsigned char *name, size_t name_len)
    {
      int32_t elem;

      for (elem = 0; elem < table_size; elem++)
	if (symb_table[2 * elem] != 0)
	  {
	    int32_t idx = symb_table[2 * elem + 1];

	    idx += 1 + extra[idx];
	    if (
		name_len == extra[idx]

		&& memcmp (name, &extra[idx + 1], name_len) == 0)

	      return elem;
	  }
      return -1;
    }


  auto inline unsigned int
  __attribute__ ((always_inline))
  lookup_collation_sequence_value (bracket_elem_t *br_elem)
    {
      if (br_elem->type == SB_CHAR)
	{


	  if (nrules == 0)
	    return collseqmb[br_elem->opr.ch];
	  else
	    {
	      wint_t wc = __btowc (br_elem->opr.ch);
	      return __collseq_table_lookup (collseqwc, wc);
	    }
	}
      else if (br_elem->type == MB_CHAR)
	{
	  if (nrules != 0)
	    return __collseq_table_lookup (collseqwc, br_elem->opr.wch);
	}
      else if (br_elem->type == COLL_SYM)
	{
	  size_t sym_name_len = strlen ((char *) br_elem->opr.name);
	  if (nrules != 0)
	    {
	      int32_t elem, idx;
	      elem = seek_collating_symbol_entry (br_elem->opr.name,
						  sym_name_len);
	      if (elem != -1)
		{

		  idx = symb_table[2 * elem + 1];

		  idx += 1 + extra[idx];

		  idx += 1 + extra[idx];

		  idx = (idx + 3) & ~3;

		  idx += sizeof (unsigned int);

		  idx += sizeof (unsigned int) *
		    (1 + *(unsigned int *) (extra + idx));

		  return *(unsigned int *) (extra + idx);
		}
	      else if (sym_name_len == 1)
		{


		  return collseqmb[br_elem->opr.name[0]];
		}
	    }
	  else if (sym_name_len == 1)
	    return collseqmb[br_elem->opr.name[0]];
	}
      return UINT_MAX;
    }


  auto inline reg_errcode_t
  __attribute__ ((always_inline))
  build_range_exp (bitset_t sbcset, re_charset_t *mbcset, int *range_alloc,
		   bracket_elem_t *start_elem, bracket_elem_t *end_elem)
    {
      unsigned int ch;
      uint32_t start_collseq;
      uint32_t end_collseq;


      if (BE (start_elem->type == EQUIV_CLASS || start_elem->type == CHAR_CLASS
	      || end_elem->type == EQUIV_CLASS || end_elem->type == CHAR_CLASS,
	      0))
	return REG_ERANGE;


      start_collseq = lookup_collation_sequence_value (start_elem);
      end_collseq = lookup_collation_sequence_value (end_elem);

      if (BE (start_collseq == UINT_MAX || end_collseq == UINT_MAX, 0))
	return REG_ECOLLATE;
      if (BE ((syntax & RE_NO_EMPTY_RANGES) && start_collseq > end_collseq, 0))
	return REG_ERANGE;


      if (nrules > 0 || dfa->mb_cur_max > 1)
	{

	  if (BE (*range_alloc == mbcset->nranges, 0))
	    {

	      uint32_t *new_array_start;
	      uint32_t *new_array_end;
	      Idx new_nranges;


	      new_nranges = 2 * mbcset->nranges + 1;
	      new_array_start = re_realloc (mbcset->range_starts, uint32_t,
					    new_nranges);
	      new_array_end = re_realloc (mbcset->range_ends, uint32_t,
					  new_nranges);

	      if (BE (new_array_start == NULL || new_array_end == NULL, 0))
		return REG_ESPACE;

	      mbcset->range_starts = new_array_start;
	      mbcset->range_ends = new_array_end;
	      *range_alloc = new_nranges;
	    }

	  mbcset->range_starts[mbcset->nranges] = start_collseq;
	  mbcset->range_ends[mbcset->nranges++] = end_collseq;
	}


      for (ch = 0; ch < SBC_MAX; ch++)
	{
	  uint32_t ch_collseq;


	  if (nrules == 0)
	    ch_collseq = collseqmb[ch];
	  else
	    ch_collseq = __collseq_table_lookup (collseqwc, __btowc (ch));
	  if (start_collseq <= ch_collseq && ch_collseq <= end_collseq)
	    bitset_set (sbcset, ch);
	}
      return REG_NOERROR;
    }


  auto inline reg_errcode_t
  __attribute__ ((always_inline))
  build_collating_symbol (bitset_t sbcset, re_charset_t *mbcset,
			  Idx *coll_sym_alloc, const unsigned char *name)
    {
      int32_t elem, idx;
      size_t name_len = strlen ((const char *) name);
      if (nrules != 0)
	{
	  elem = seek_collating_symbol_entry (name, name_len);
	  if (elem != -1)
	    {

	      idx = symb_table[2 * elem + 1];

	      idx += 1 + extra[idx];
	    }
	  else if (name_len == 1)
	    {


	      bitset_set (sbcset, name[0]);
	      return REG_NOERROR;
	    }
	  else
	    return REG_ECOLLATE;


	  if (BE (*coll_sym_alloc == mbcset->ncoll_syms, 0))
	    {


	      Idx new_coll_sym_alloc = 2 * mbcset->ncoll_syms + 1;


	      int32_t *new_coll_syms = re_realloc (mbcset->coll_syms, int32_t,
						   new_coll_sym_alloc);
	      if (BE (new_coll_syms == NULL, 0))
		return REG_ESPACE;
	      mbcset->coll_syms = new_coll_syms;
	      *coll_sym_alloc = new_coll_sym_alloc;
	    }
	  mbcset->coll_syms[mbcset->ncoll_syms++] = idx;
	  return REG_NOERROR;
	}
      else
	{
	  if (BE (name_len != 1, 0))
	    return REG_ECOLLATE;
	  else
	    {
	      bitset_set (sbcset, name[0]);
	      return REG_NOERROR;
	    }
	}
    }
#endif

  re_token_t br_token;
  re_bitset_ptr_t sbcset;
#ifdef RE_ENABLE_I18N
  re_charset_t *mbcset;
  Idx coll_sym_alloc = 0, range_alloc = 0, mbchar_alloc = 0;
  Idx equiv_class_alloc = 0, char_class_alloc = 0;
#endif
  bool non_match = false;
  bin_tree_t *work_tree;
  int token_len;
  bool first_round = true;
#ifdef _LIBC
  collseqmb = (const unsigned char *)
    _NL_CURRENT (LC_COLLATE, _NL_COLLATE_COLLSEQMB);
  nrules = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES);
  if (nrules)
    {


      collseqwc = _NL_CURRENT (LC_COLLATE, _NL_COLLATE_COLLSEQWC);
      table_size = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_SYMB_HASH_SIZEMB);
      symb_table = (const int32_t *) _NL_CURRENT (LC_COLLATE,
						  _NL_COLLATE_SYMB_TABLEMB);
      extra = (const unsigned char *) _NL_CURRENT (LC_COLLATE,
						   _NL_COLLATE_SYMB_EXTRAMB);
    }
#endif
  sbcset = (re_bitset_ptr_t) calloc (sizeof (bitset_t), 1);
#ifdef RE_ENABLE_I18N
  mbcset = (re_charset_t *) calloc (sizeof (re_charset_t), 1);
#endif
#ifdef RE_ENABLE_I18N
  if (BE (sbcset == NULL || mbcset == NULL, 0))
#else
  if (BE (sbcset == NULL, 0))
#endif
    {
      re_free (sbcset);
#ifdef RE_ENABLE_I18N
      re_free (mbcset);
#endif
      *err = REG_ESPACE;
      return NULL;
    }

  token_len = peek_token_bracket (token, regexp, syntax);
  if (BE (token->type == END_OF_RE, 0))
    {
      *err = REG_BADPAT;
      goto parse_bracket_exp_free_return;
    }
  if (token->type == OP_NON_MATCH_LIST)
    {
#ifdef RE_ENABLE_I18N
      mbcset->non_match = 1;
#endif
      non_match = true;
      if (syntax & RE_HAT_LISTS_NOT_NEWLINE)
	bitset_set (sbcset, '\n');
      re_string_skip_bytes (regexp, token_len);
      token_len = peek_token_bracket (token, regexp, syntax);
      if (BE (token->type == END_OF_RE, 0))
	{
	  *err = REG_BADPAT;
	  goto parse_bracket_exp_free_return;
	}
    }


  if (token->type == OP_CLOSE_BRACKET)
    token->type = CHARACTER;

  while (1)
    {
      bracket_elem_t start_elem, end_elem;
      unsigned char start_name_buf[BRACKET_NAME_BUF_SIZE];
      unsigned char end_name_buf[BRACKET_NAME_BUF_SIZE];
      reg_errcode_t ret;
      int token_len2 = 0;
      bool is_range_exp = false;
      re_token_t token2;

      start_elem.opr.name = start_name_buf;
      start_elem.type = COLL_SYM;
      ret = parse_bracket_element (&start_elem, regexp, token, token_len, dfa,
				   syntax, first_round);
      if (BE (ret != REG_NOERROR, 0))
	{
	  *err = ret;
	  goto parse_bracket_exp_free_return;
	}
      first_round = false;


      token_len = peek_token_bracket (token, regexp, syntax);


      if (start_elem.type != CHAR_CLASS && start_elem.type != EQUIV_CLASS)
	{
	  if (BE (token->type == END_OF_RE, 0))
	    {
	      *err = REG_EBRACK;
	      goto parse_bracket_exp_free_return;
	    }
	  if (token->type == OP_CHARSET_RANGE)
	    {
	      re_string_skip_bytes (regexp, token_len);
	      token_len2 = peek_token_bracket (&token2, regexp, syntax);
	      if (BE (token2.type == END_OF_RE, 0))
		{
		  *err = REG_EBRACK;
		  goto parse_bracket_exp_free_return;
		}
	      if (token2.type == OP_CLOSE_BRACKET)
		{

		  re_string_skip_bytes (regexp, -token_len);
		  token->type = CHARACTER;
		}
	      else
		is_range_exp = true;
	    }
	}

      if (is_range_exp == true)
	{
	  end_elem.opr.name = end_name_buf;
	  end_elem.type = COLL_SYM;
	  ret = parse_bracket_element (&end_elem, regexp, &token2, token_len2,
				       dfa, syntax, true);
	  if (BE (ret != REG_NOERROR, 0))
	    {
	      *err = ret;
	      goto parse_bracket_exp_free_return;
	    }

	  token_len = peek_token_bracket (token, regexp, syntax);

#ifdef _LIBC
	  *err = build_range_exp (sbcset, mbcset, &range_alloc,
				  &start_elem, &end_elem);
#else
# ifdef RE_ENABLE_I18N
	  *err = build_range_exp (syntax, sbcset,
				  dfa->mb_cur_max > 1 ? mbcset : NULL,
				  &range_alloc, &start_elem, &end_elem);
# else
	  *err = build_range_exp (syntax, sbcset, &start_elem, &end_elem);
# endif
#endif
	  if (BE (*err != REG_NOERROR, 0))
	    goto parse_bracket_exp_free_return;
	}
      else
	{
	  switch (start_elem.type)
	    {
	    case SB_CHAR:
	      bitset_set (sbcset, start_elem.opr.ch);
	      break;
#ifdef RE_ENABLE_I18N
	    case MB_CHAR:

	      if (BE (mbchar_alloc == mbcset->nmbchars, 0))
		{
		  wchar_t *new_mbchars;


		  mbchar_alloc = 2 * mbcset->nmbchars + 1;

		  new_mbchars = re_realloc (mbcset->mbchars, wchar_t,
					    mbchar_alloc);
		  if (BE (new_mbchars == NULL, 0))
		    goto parse_bracket_exp_espace;
		  mbcset->mbchars = new_mbchars;
		}
	      mbcset->mbchars[mbcset->nmbchars++] = start_elem.opr.wch;
	      break;
#endif
	    case EQUIV_CLASS:
	      *err = build_equiv_class (sbcset,
#ifdef RE_ENABLE_I18N
					mbcset, &equiv_class_alloc,
#endif
					start_elem.opr.name);
	      if (BE (*err != REG_NOERROR, 0))
		goto parse_bracket_exp_free_return;
	      break;
	    case COLL_SYM:
	      *err = build_collating_symbol (sbcset,
#ifdef RE_ENABLE_I18N
					     mbcset, &coll_sym_alloc,
#endif
					     start_elem.opr.name);
	      if (BE (*err != REG_NOERROR, 0))
		goto parse_bracket_exp_free_return;
	      break;
	    case CHAR_CLASS:
	      *err = build_charclass (regexp->trans, sbcset,
#ifdef RE_ENABLE_I18N
				      mbcset, &char_class_alloc,
#endif
				      (const char *) start_elem.opr.name,
				      syntax);
	      if (BE (*err != REG_NOERROR, 0))
	       goto parse_bracket_exp_free_return;
	      break;
	    default:
	      assert (0);
	      break;
	    }
	}
      if (BE (token->type == END_OF_RE, 0))
	{
	  *err = REG_EBRACK;
	  goto parse_bracket_exp_free_return;
	}
      if (token->type == OP_CLOSE_BRACKET)
	break;
    }

  re_string_skip_bytes (regexp, token_len);


  if (non_match)
    bitset_not (sbcset);

#ifdef RE_ENABLE_I18N

  if (dfa->mb_cur_max > 1)
    bitset_mask (sbcset, dfa->sb_char);

  if (mbcset->nmbchars || mbcset->ncoll_syms || mbcset->nequiv_classes
      || mbcset->nranges || (dfa->mb_cur_max > 1 && (mbcset->nchar_classes
						     || mbcset->non_match)))
    {
      bin_tree_t *mbc_tree;
      int sbc_idx;

      dfa->has_mb_node = 1;
      br_token.type = COMPLEX_BRACKET;
      br_token.opr.mbcset = mbcset;
      mbc_tree = create_token_tree (dfa, NULL, NULL, &br_token);
      if (BE (mbc_tree == NULL, 0))
	goto parse_bracket_exp_espace;
      for (sbc_idx = 0; sbc_idx < BITSET_WORDS; ++sbc_idx)
	if (sbcset[sbc_idx])
	  break;


      if (sbc_idx < BITSET_WORDS)
	{

	  br_token.type = SIMPLE_BRACKET;
	  br_token.opr.sbcset = sbcset;
	  work_tree = create_token_tree (dfa, NULL, NULL, &br_token);
	  if (BE (work_tree == NULL, 0))
	    goto parse_bracket_exp_espace;


	  work_tree = create_tree (dfa, work_tree, mbc_tree, OP_ALT);
	  if (BE (work_tree == NULL, 0))
	    goto parse_bracket_exp_espace;
	}
      else
	{
	  re_free (sbcset);
	  work_tree = mbc_tree;
	}
    }
  else
#endif
    {
#ifdef RE_ENABLE_I18N
      free_charset (mbcset);
#endif

      br_token.type = SIMPLE_BRACKET;
      br_token.opr.sbcset = sbcset;
      work_tree = create_token_tree (dfa, NULL, NULL, &br_token);
      if (BE (work_tree == NULL, 0))
	goto parse_bracket_exp_espace;
    }
  return work_tree;

 parse_bracket_exp_espace:
  *err = REG_ESPACE;
 parse_bracket_exp_free_return:
  re_free (sbcset);
#ifdef RE_ENABLE_I18N
  free_charset (mbcset);
#endif
  return NULL;
}
