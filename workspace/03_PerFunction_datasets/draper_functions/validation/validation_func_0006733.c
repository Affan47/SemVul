read_xml_file(char *fname)
{

  xmlDocPtr doc;

  g_return_val_if_fail(fname!=NULL, FALSE);


  doc = xmlParseFile(fname);


  if(!doc)
    return FALSE;

  if(
     !doc->children ||

     !doc->children->name ||

     g_ascii_strcasecmp((char *)doc->children->name,"ImageId")!=0) {
    xmlFreeDoc(doc);
    return FALSE;
  }

  parse_doc(doc);
  xmlFreeDoc(doc);
  return TRUE;
}
