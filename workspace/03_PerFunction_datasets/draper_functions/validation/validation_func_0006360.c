itable_print_names (lf *file, filter *set, char *name)
{
  char *elem;
  lf_printf (file, "const char *%sitable_%s_names[nr_%sitable_%ss + 1] = {\n",
	     options.module.itable.prefix.l, name,
	     options.module.itable.prefix.l, name);
  lf_indent (file, +2);
  for (elem = filter_next (set, "");
       elem != NULL; elem = filter_next (set, elem))
    {
      lf_printf (file, "\"%s\",\n", elem);
    }
  lf_printf (file, "0,\n");
  lf_indent (file, -2);
  lf_printf (file, "};\n");
}
