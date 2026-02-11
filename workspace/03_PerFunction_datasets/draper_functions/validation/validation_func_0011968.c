command_machinetags_getPairs(flickcurl* fc, int argc, char *argv[])
{
  const char *nspace = NULL;
  const char* predicate = NULL;
  int per_page = 10;
  int page = 0;
  flickcurl_tag_predicate_value** tag_pvs = NULL;

  if(argc >1) {
    nspace = argv[1];
    if(argc >2) {
      predicate = argv[2];
      if(argc >3) {
        per_page = parse_page_param(argv[3]);
        if(argc >4) {
          page = parse_page_param(argv[4]);
        }
      }
    }
  }

  tag_pvs = flickcurl_machinetags_getPairs(fc, nspace, predicate, per_page,
                                           page);
  if(tag_pvs) {
    command_print_predicate_values(tag_pvs, "getPairs returned");
    flickcurl_free_tag_predicate_values(tag_pvs);
  }

  return (tag_pvs == NULL);
}
