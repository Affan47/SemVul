finish_newstyle_options (uint64_t *exportsize,
                         const char *exportname_in, uint32_t exportnamelen)
{
  GET_CONN;


  CLEANUP_FREE char *exportname = strndup (exportname_in, exportnamelen);
  if (exportname == NULL) {
    nbdkit_error ("strndup: %m");
    return -1;
  }


  if (conn->exportname_from_set_meta_context &&
      strcmp (conn->exportname_from_set_meta_context, exportname) != 0) {
    debug ("newstyle negotiation: NBD_OPT_SET_META_CONTEXT export name \"%s\" "
           "≠ final client exportname \"%s\", "
           "so discarding the previous context",
           conn->exportname_from_set_meta_context, exportname);
    conn->meta_context_base_allocation = false;
  }

  if (protocol_common_open (exportsize, &conn->eflags, exportname) == -1)
    return -1;

  debug ("newstyle negotiation: flags: export 0x%x", conn->eflags);
  return 0;
}
