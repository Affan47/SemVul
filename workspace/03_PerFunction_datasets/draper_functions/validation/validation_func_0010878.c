main(int argc, char* argv[])
{
  GError* error = NULL;
  xmlDocPtr doc;
  gboolean ret;

  if(!inf_init(&error))
  {
    fprintf(stderr, "%s\n", error->message);
    return -1;
  }

  if(!g_file_test(REPLAY, G_FILE_TEST_IS_EXECUTABLE))
  {
    fprintf(stderr, "Replay tool not available. Run \"make\" first.");
    return -1;
  }

  if(argc < 2)
  {
    fprintf(stderr, "Usage: %s <record-file>\n", argv[0]);
    return -1;
  }

  doc = xmlReadFile(argv[1], "UTF-8", XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
  if(!doc || !xmlDocGetRootElement(doc))
  {
    if(doc) xmlFreeDoc(doc);
    fprintf(stderr, "%s\n", xmlGetLastError()->message);
    return -1;
  }

  ret = inf_test_reduce_replay_reduce(doc, argv[1]);

  xmlFreeDoc(doc);
  return ret ? 0 : -1;
}
