begin_scope (scope_kind kind, tree entity)
{
  cxx_scope *scope;


  if (!ENABLE_SCOPE_CHECKING && free_binding_level)
    {
      scope = free_binding_level;
      free_binding_level = scope->level_chain;
    }
  else
    scope = ggc_alloc (sizeof (cxx_scope));
  memset (scope, 0, sizeof (cxx_scope));

  scope->this_entity = entity;
  scope->more_cleanups_ok = true;
  switch (kind)
    {
    case sk_cleanup:
      scope->keep = true;
      break;

    case sk_template_spec:
      scope->explicit_spec_p = true;
      kind = sk_template_parms;

    case sk_template_parms:
    case sk_block:
    case sk_try:
    case sk_catch:
    case sk_for:
    case sk_class:
    case sk_function_parms:
      scope->keep = keep_next_level_flag;
      break;

    case sk_namespace:
      scope->type_decls = binding_table_new (namespace_scope_ht_size (entity));
      NAMESPACE_LEVEL (entity) = scope;
      VARRAY_TREE_INIT (scope->static_decls,
                        DECL_NAME (entity) == std_identifier
                        || DECL_NAME (entity) == global_scope_name
                        ? 200 : 10,
                        "Static declarations");
      break;

    default:

      my_friendly_assert (false, 20030922);
      break;
    }
  scope->kind = kind;


  scope->level_chain = current_binding_level;
  current_binding_level = scope;
  keep_next_level_flag = false;

  if (ENABLE_SCOPE_CHECKING)
    {
      scope->binding_depth = binding_depth;
      indent (binding_depth);
      cxx_scope_debug (scope, input_location.line, "push");
      is_class_level = 0;
      binding_depth++;
    }

  return scope;
}
