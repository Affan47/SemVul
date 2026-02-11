getTimeDisplayFormat( xmlDocPtr optionXML )
{
   GString *format=NULL;
   xmlNodePtr cur;
   xmlChar *formatText;

   cur = xmlDocGetRootElement(optionXML);
   if (cur != NULL)
   {
      if (xmlStrcmp(cur->name, ROOT_NODE)) {
	 fprintf(stderr,"Options file incorrectly formatted\n");
	 return NULL;
      }

      cur = cur->xmlChildrenNode;
      while ( (cur != NULL) && (format==NULL) )
      {
	 if ((!xmlStrcmp(cur->name, TIME_DISPLAY_FORMAT_NODE)))
	 {
	    formatText = xmlNodeListGetString(optionXML,
					      cur->xmlChildrenNode, 1);
	    format = g_string_new(formatText);
	    xmlFree(formatText);
	    return format;
	 }
	 cur = cur->next;
      }

   }

   return format;
}
