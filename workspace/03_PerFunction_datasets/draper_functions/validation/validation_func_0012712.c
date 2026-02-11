bad_specifiers (tree object,
		enum bad_spec_place type,
		int virtualp,
		int quals,
		int inlinep,
		int friendp,
		int raises)
{
  switch (type)
    {
      case BSP_VAR:
	if (virtualp)
	  error ("%qD declared as a %<virtual%> variable", object);
	if (inlinep)
	  error ("%qD declared as an %<inline%> variable", object);
	if (quals)
	  error ("%<const%> and %<volatile%> function specifiers on "
	         "%qD invalid in variable declaration", object);
	break;
      case BSP_PARM:
	if (virtualp)
	  error ("%qD declared as a %<virtual%> parameter", object);
	if (inlinep)
	  error ("%qD declared as an %<inline%> parameter", object);
	if (quals)
	  error ("%<const%> and %<volatile%> function specifiers on "
	  	 "%qD invalid in parameter declaration", object);
	break;
      case BSP_TYPE:
	if (virtualp)
	  error ("%qD declared as a %<virtual%> type", object);
	if (inlinep)
	  error ("%qD declared as an %<inline%> type", object);
	if (quals)
	  error ("%<const%> and %<volatile%> function specifiers on "
	  	 "%qD invalid in type declaration", object);
	break;
      case BSP_FIELD:
	if (virtualp)
	  error ("%qD declared as a %<virtual%> field", object);
	if (inlinep)
	  error ("%qD declared as an %<inline%> field", object);
	if (quals)
	  error ("%<const%> and %<volatile%> function specifiers on "
	  	 "%qD invalid in field declaration", object);
	break;
      default:
        gcc_unreachable();
    }
  if (friendp)
    error ("%q+D declared as a friend", object);
  if (raises
      && (TREE_CODE (object) == TYPE_DECL
	  || (!TYPE_PTRFN_P (TREE_TYPE (object))
	      && !TYPE_REFFN_P (TREE_TYPE (object))
	      && !TYPE_PTRMEMFUNC_P (TREE_TYPE (object)))))
    error ("%q+D declared with an exception specification", object);
}
