get_minimal_subprog_decl (Entity_Id gnat_entity)
{
  tree gnu_entity_name, gnu_ext_name;
  struct attrib *attr_list = NULL;


  while (Present (Alias (gnat_entity)))
    {
      gnat_entity = Alias (gnat_entity);
      if (present_gnu_tree (gnat_entity))
	return get_gnu_tree (gnat_entity);
    }

  gnu_entity_name = get_entity_name (gnat_entity);
  gnu_ext_name = create_concat_name (gnat_entity, NULL);

  if (Has_Stdcall_Convention (gnat_entity))
    prepend_one_attribute_to (&attr_list, ATTR_MACHINE_ATTRIBUTE,
			      get_identifier ("stdcall"), NULL_TREE,
			      gnat_entity);
  else if (Has_Thiscall_Convention (gnat_entity))
    prepend_one_attribute_to (&attr_list, ATTR_MACHINE_ATTRIBUTE,
			      get_identifier ("thiscall"), NULL_TREE,
			      gnat_entity);

  if (No (Interface_Name (gnat_entity)) && gnu_ext_name == gnu_entity_name)
    gnu_ext_name = NULL_TREE;

  return
    create_subprog_decl (gnu_entity_name, gnu_ext_name, void_ftype, NULL_TREE,
			 false, true, true, true, attr_list, gnat_entity);
}
