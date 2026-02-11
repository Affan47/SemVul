write_source_name (tree identifier)
{
  MANGLE_TRACE_TREE ("source-name", identifier);


  if (IDENTIFIER_TEMPLATE (identifier))
    identifier = IDENTIFIER_TEMPLATE (identifier);

  write_unsigned_number (IDENTIFIER_LENGTH (identifier));
  write_identifier (IDENTIFIER_POINTER (identifier));
}
