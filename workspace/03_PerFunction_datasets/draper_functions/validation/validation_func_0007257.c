innermost_non_namespace_value (tree name)
{
  cxx_binding *binding;
  binding = outer_binding (name, NULL, true);
  return binding ? binding->value : NULL_TREE;
}
