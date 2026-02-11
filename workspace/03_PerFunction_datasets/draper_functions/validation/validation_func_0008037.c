set_instantiated_value (htab_t cache, basic_block instantiated_below,
			tree version, tree val)
{
  struct scev_info_str *info, pattern;
  PTR *slot;

  pattern.var = version;
  pattern.instantiated_below = instantiated_below;
  slot = htab_find_slot (cache, &pattern, INSERT);

  if (!*slot)
    *slot = new_scev_info_str (instantiated_below, version);
  info = (struct scev_info_str *) *slot;
  info->chrec = val;
}
