decode_xform (char *file_name, void *data)
{
  int type = *(int*)data;

  switch (type)
    {
    case XFORM_SYMLINK:


      return file_name;

    case XFORM_LINK:
      file_name = safer_name_suffix (file_name, true, absolute_names_option);
      break;

    case XFORM_REGFILE:
      file_name = safer_name_suffix (file_name, false, absolute_names_option);
      break;
    }

  if (strip_name_components)
    {
      size_t prefix_len = stripped_prefix_len (file_name,
					       strip_name_components);
      if (prefix_len == (size_t) -1)
	prefix_len = strlen (file_name);
      file_name += prefix_len;
    }
  return file_name;
}
