maybe_dummy_object (tree type, tree* binfop)
{
  tree decl, context;
  tree binfo;
  tree current = current_nonlambda_class_type ();

  if (current
      && (binfo = lookup_base (current, type, ba_any, NULL)))
    context = current;
  else
    {

      context = type;
      binfo = TYPE_BINFO (type);
    }

  if (binfop)
    *binfop = binfo;

  if (current_class_ref


      && (same_type_ignoring_top_level_qualifiers_p
	  (TREE_TYPE (current_class_ref), context)))
    decl = current_class_ref;
  else if (current != current_class_type
	   && context == nonlambda_method_basetype ())

    decl = (build_x_indirect_ref
	    ((lambda_expr_this_capture
	      (CLASSTYPE_LAMBDA_EXPR (current_class_type))),
	     RO_NULL, tf_warning_or_error));
  else
    decl = build_dummy_object (context);

  return decl;
}
