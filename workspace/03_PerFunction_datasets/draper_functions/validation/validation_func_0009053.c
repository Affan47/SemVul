check_pattern (gcv_object_t *pat, pcre** compiled_pattern,
                           pcre_extra** study)
{
  *pat = check_classname(*pat,O(object_pcre__pattern));

  *compiled_pattern =
    (pcre*)TheFpointer(TheStructure(*pat)->recdata[1])->fp_pointer;
  if (nullp(TheStructure(*pat)->recdata[2])) *study = NULL;
  else *study =
    (pcre_extra*)TheFpointer(TheStructure(*pat)->recdata[2])->fp_pointer;
}
