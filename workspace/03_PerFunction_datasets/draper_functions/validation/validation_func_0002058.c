i386_pe_assemble_visibility (tree decl,
			     int vis ATTRIBUTE_UNUSED)
{
  if (!decl
      || !lookup_attribute ("visibility", DECL_ATTRIBUTES (decl)))
    return;
  if (!DECL_ARTIFICIAL (decl))
    warning (OPT_Wattributes, "visibility attribute not supported "
			      "in this configuration; ignored");
}
