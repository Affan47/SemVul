supplement_binding_1 (cxx_binding *binding, tree decl)
{
  tree bval = binding->value;
  bool ok = true;
  tree target_bval = strip_using_decl (bval);
  tree target_decl = strip_using_decl (decl);

  if (TREE_CODE (target_decl) == TYPE_DECL && DECL_ARTIFICIAL (target_decl)
      && target_decl != target_bval
      && (TREE_CODE (target_bval) != TYPE_DECL


	  || (processing_template_decl
	      && TREE_CODE (TREE_TYPE (target_decl)) == ENUMERAL_TYPE
	      && TREE_CODE (TREE_TYPE (target_bval)) == ENUMERAL_TYPE
	      && (dependent_type_p (ENUM_UNDERLYING_TYPE
				    (TREE_TYPE (target_decl)))
		  || dependent_type_p (ENUM_UNDERLYING_TYPE
				       (TREE_TYPE (target_bval)))))))

    binding->type = decl;
  else if (


	   !target_bval


	   || target_bval == error_mark_node


	   || (TREE_CODE (target_bval) == FUNCTION_DECL
	       && DECL_ANTICIPATED (target_bval)
	       && !DECL_HIDDEN_FRIEND_P (target_bval)))
    binding->value = decl;
  else if (TREE_CODE (target_bval) == TYPE_DECL
	   && DECL_ARTIFICIAL (target_bval)
	   && target_decl != target_bval
	   && (TREE_CODE (target_decl) != TYPE_DECL
	       || same_type_p (TREE_TYPE (target_decl),
			       TREE_TYPE (target_bval))))
    {


      binding->type = bval;
      binding->value = decl;
      binding->value_is_inherited = false;
    }
  else if (TREE_CODE (target_bval) == TYPE_DECL
	   && TREE_CODE (target_decl) == TYPE_DECL
	   && DECL_NAME (target_decl) == DECL_NAME (target_bval)
	   && binding->scope->kind != sk_class
	   && (same_type_p (TREE_TYPE (target_decl), TREE_TYPE (target_bval))


	       || uses_template_parms (TREE_TYPE (target_decl))
	       || uses_template_parms (TREE_TYPE (target_bval))))


    ok = false;


  else if (TREE_CODE (target_decl) == VAR_DECL
	   && TREE_CODE (target_bval) == VAR_DECL
	   && DECL_EXTERNAL (target_decl) && DECL_EXTERNAL (target_bval)
	   && !DECL_CLASS_SCOPE_P (target_decl))
    {
      duplicate_decls (decl, binding->value, false);
      ok = false;
    }
  else if (TREE_CODE (decl) == NAMESPACE_DECL
	   && TREE_CODE (bval) == NAMESPACE_DECL
	   && DECL_NAMESPACE_ALIAS (decl)
	   && DECL_NAMESPACE_ALIAS (bval)
	   && ORIGINAL_NAMESPACE (bval) == ORIGINAL_NAMESPACE (decl))


    ok = false;
  else
    {
      diagnose_name_conflict (decl, bval);
      ok = false;
    }

  return ok;
}
