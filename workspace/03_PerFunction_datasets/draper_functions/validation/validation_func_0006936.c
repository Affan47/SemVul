mailimap_uidplus_parse(int calling_parser, mailstream * fd,
    MMAPString * buffer, size_t * indx,
    struct mailimap_extension_data ** result,
    size_t progr_rate,
    progress_function * progr_fun)
{
  if (calling_parser != MAILIMAP_EXTENDED_PARSER_RESP_TEXT_CODE)
    return MAILIMAP_ERROR_PARSE;

  return mailimap_uidplus_resp_code_parse(fd, buffer, indx, result);
}
