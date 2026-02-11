lto_resolution_read (splay_tree file_ids, FILE *resolution, lto_file *file)
{


  unsigned int name_len;
  char *obj_name;
  unsigned int num_symbols;
  unsigned int i;
  struct lto_file_decl_data *file_data;
  unsigned max_index = 0;
  splay_tree_node nd = NULL;

  if (!resolution)
    return;

  name_len = strlen (file->filename);
  obj_name = XNEWVEC (char, name_len + 1);
  fscanf (resolution, " ");

  fread (obj_name, sizeof (char), name_len, resolution);
  obj_name[name_len] = '\0';
  if (strcmp (obj_name, file->filename) != 0)
    internal_error ("unexpected file name %s in linker resolution file. "
		    "Expected %s", obj_name, file->filename);
  if (file->offset != 0)
    {
      int t;
      char offset_p[17];
      HOST_WIDEST_INT offset;
      t = fscanf (resolution, "@0x%16s", offset_p);
      if (t != 1)
        internal_error ("could not parse file offset");
      offset = lto_parse_hex (offset_p);
      if (offset != file->offset)
        internal_error ("unexpected offset");
    }

  free (obj_name);

  fscanf (resolution, "%u", &num_symbols);

  for (i = 0; i < num_symbols; i++)
    {
      int t;
      unsigned index, id;
      char r_str[27];
      enum ld_plugin_symbol_resolution r = (enum ld_plugin_symbol_resolution) 0;
      unsigned int j;
      unsigned int lto_resolution_str_len =
	sizeof (lto_resolution_str) / sizeof (char *);

      t = fscanf (resolution, "%u %x %26s %*[^\n]\n", &index, &id, r_str);
      if (t != 3)
        internal_error ("invalid line in the resolution file");
      if (index > max_index)
	max_index = index;

      for (j = 0; j < lto_resolution_str_len; j++)
	{
	  if (strcmp (lto_resolution_str[j], r_str) == 0)
	    {
	      r = (enum ld_plugin_symbol_resolution) j;
	      break;
	    }
	}
      if (j == lto_resolution_str_len)
	internal_error ("invalid resolution in the resolution file");

      if (!(nd && nd->key == id))
	{
	  nd = splay_tree_lookup (file_ids, id);
	  if (nd == NULL)
	    internal_error ("resolution sub id %x not in object file", id);
	}

      file_data = (struct lto_file_decl_data *)nd->value;
      if (cgraph_dump_file)
	fprintf (cgraph_dump_file, "Adding resolution %u %u to id %x\n",
		 index, r, file_data->id);
      VEC_safe_grow_cleared (ld_plugin_symbol_resolution_t, heap,
			     file_data->resolutions,
			     max_index + 1);
      VEC_replace (ld_plugin_symbol_resolution_t,
		   file_data->resolutions, index, r);
    }
}
