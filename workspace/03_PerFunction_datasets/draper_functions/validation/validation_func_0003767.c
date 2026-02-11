build_exception_variant (tree type, tree raises)
{
  tree v = TYPE_MAIN_VARIANT (type);
  int type_quals = TYPE_QUALS (type);

  for (; v; v = TYPE_NEXT_VARIANT (v))
    if (TYPE_QUALS (v) == type_quals
        && comp_except_specs (raises, TYPE_RAISES_EXCEPTIONS (v), 1)
	&& (*targetm.comp_type_attributes) (type, v))
      return v;


  v = build_type_copy (type);
  TYPE_RAISES_EXCEPTIONS (v) = raises;
  return v;
}
