onigenc_unicode_case_map(OnigCaseFoldType* flagP,
    const OnigUChar** pp, const OnigUChar* end,
    OnigUChar* to, OnigUChar* to_end,
    const struct OnigEncodingTypeST* enc)
{
  OnigCodePoint code;
  OnigUChar *to_start = to;
  OnigCaseFoldType flags = *flagP;
  int codepoint_length;

  to_end -= CASE_MAPPING_SLACK;


  flags |= (flags & (ONIGENC_CASE_UPCASE | ONIGENC_CASE_DOWNCASE)) << ONIGENC_CASE_SPECIAL_OFFSET;

  while (*pp < end && to <= to_end) {
    codepoint_length = ONIGENC_PRECISE_MBC_ENC_LEN(enc, *pp, end);
    if (codepoint_length < 0)
      return codepoint_length;
    code = ONIGENC_MBC_TO_CODE(enc, *pp, end);
    *pp += codepoint_length;

    if (code <= 'z') {
      if (code >= 'a' && code <= 'z') {
	if (flags & ONIGENC_CASE_UPCASE) {
	  MODIFIED;
	  if (flags & ONIGENC_CASE_FOLD_TURKISH_AZERI && code == 'i')
	    code = I_WITH_DOT_ABOVE;
	  else
	    code += 'A' - 'a';
	}
      }
      else if (code >= 'A' && code <= 'Z') {
	if (flags & (ONIGENC_CASE_DOWNCASE | ONIGENC_CASE_FOLD)) {
	  MODIFIED;
	  if (flags & ONIGENC_CASE_FOLD_TURKISH_AZERI && code == 'I')
	    code = DOTLESS_i;
	  else
	    code += 'a' - 'A';
	}
      }
    }
    else if (!(flags & ONIGENC_CASE_ASCII_ONLY) && code >= 0x00B5) {
      const CodePointList3 *folded;

      if (code == I_WITH_DOT_ABOVE) {
	if (flags & (ONIGENC_CASE_DOWNCASE | ONIGENC_CASE_FOLD)) {
	  MODIFIED;
	  code = 'i';
	  if (!(flags & ONIGENC_CASE_FOLD_TURKISH_AZERI)) {
	    to += ONIGENC_CODE_TO_MBC(enc, code, to);
	    code = DOT_ABOVE;
	  }
	}
      }
      else if (code == DOTLESS_i) {
	if (flags & ONIGENC_CASE_UPCASE) {
	  MODIFIED;
	  code = 'I';
	}
      }
      else if ((folded = onigenc_unicode_fold_lookup(code)) != 0) {
	if ((flags & ONIGENC_CASE_TITLECASE)
	    && (OnigCaseFoldFlags(folded->n) & ONIGENC_CASE_IS_TITLECASE)) {

	}
	else if (flags & OnigCaseFoldFlags(folded->n)) {
	  const OnigCodePoint *next;
	  int count;

	  MODIFIED;
	  if (flags & OnigCaseFoldFlags(folded->n) & ONIGENC_CASE_SPECIALS) {
	    const OnigCodePoint *SpecialsStart = CaseMappingSpecials + OnigSpecialIndexDecode(folded->n);

	    if (OnigCaseFoldFlags(folded->n) & ONIGENC_CASE_IS_TITLECASE) {
	      if ((flags & (ONIGENC_CASE_UPCASE | ONIGENC_CASE_DOWNCASE))
		  == (ONIGENC_CASE_UPCASE | ONIGENC_CASE_DOWNCASE))
		goto SpecialsCopy;
	      else
		SpecialsStart += SpecialsLengthExtract(*SpecialsStart);
	    }
	    if (OnigCaseFoldFlags(folded->n) & ONIGENC_CASE_TITLECASE) {
	      if (flags & ONIGENC_CASE_TITLECASE)
		goto SpecialsCopy;
	      else
		SpecialsStart += SpecialsLengthExtract(*SpecialsStart);
	    }
	    if (OnigCaseFoldFlags(folded->n) & ONIGENC_CASE_DOWN_SPECIAL) {
	      if (!(flags & ONIGENC_CASE_DOWN_SPECIAL))
		SpecialsStart += SpecialsLengthExtract(*SpecialsStart);
	    }

SpecialsCopy:
	    count = SpecialsLengthExtract(*SpecialsStart);
	    next = SpecialsStart;
	    code = SpecialsCodepointExtract(*next++);
	  }
	  else {
	    count = OnigCodePointCount(folded->n);
	    next = folded->code;
	    code = *next++;
	  }
	  if (count == 1)
	    ;
	  else if (count == 2) {
	    to += ONIGENC_CODE_TO_MBC(enc, code, to);
	    code = *next;
	  }
	  else {
	    to += ONIGENC_CODE_TO_MBC(enc, code, to);
	    to += ONIGENC_CODE_TO_MBC(enc, *next++, to);
	    code = *next;
	  }
	}
      }
      else if ((folded = onigenc_unicode_unfold1_lookup(code)) != 0
	  && flags & OnigCaseFoldFlags(folded->n)) {
	MODIFIED;
	code = folded->code[(flags & OnigCaseFoldFlags(folded->n) & ONIGENC_CASE_TITLECASE) ? 1 : 0];
      }
    }
    to += ONIGENC_CODE_TO_MBC(enc, code, to);

    if (flags & ONIGENC_CASE_TITLECASE)
      flags ^= (ONIGENC_CASE_UPCASE | ONIGENC_CASE_DOWNCASE | ONIGENC_CASE_TITLECASE |
	  ONIGENC_CASE_UP_SPECIAL | ONIGENC_CASE_DOWN_SPECIAL);
  }
  *flagP = flags;
  return (int )(to - to_start);
}
