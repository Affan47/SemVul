convert_from_reference (tree val)
{
  if (TREE_TYPE (val)
      && TREE_CODE (TREE_TYPE (val)) == REFERENCE_TYPE)
    {
      tree t = TREE_TYPE (TREE_TYPE (val));
      tree ref = build1 (INDIRECT_REF, t, val);

      mark_exp_read (val);


      TREE_READONLY (ref) = CP_TYPE_CONST_P (t);
      TREE_THIS_VOLATILE (ref) = CP_TYPE_VOLATILE_P (t);
      TREE_SIDE_EFFECTS (ref)
	= (TREE_THIS_VOLATILE (ref) || TREE_SIDE_EFFECTS (val));
      val = ref;
    }

  return val;
}
