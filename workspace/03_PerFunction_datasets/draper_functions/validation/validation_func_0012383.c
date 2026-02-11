mxml_end_element(MXML_WRITER *writer)
{
   int i;
   char line[1000];

   if (writer->level == 0)
      return 0;

   writer->level--;

   if (writer->element_is_open) {
      writer->element_is_open = FALSE;
      mxml_free(writer->stack[writer->level]);
      if (writer->level == 0)
         mxml_free(writer->stack);
      strcpy(line, "/>\n");
      return mxml_write_line(writer, line) == (int)strlen(line);
   }

   line[0] = 0;
   if (!writer->data_was_written) {
      for (i=0 ; i<writer->level ; i++)
         rb::strlcat(line, XML_INDENT, sizeof(line));
   }

   rb::strlcat(line, "</", sizeof(line));
   rb::strlcat(line, writer->stack[writer->level], sizeof(line));
   mxml_free(writer->stack[writer->level]);
   if (writer->level == 0)
      mxml_free(writer->stack);
   rb::strlcat(line, ">\n", sizeof(line));
   writer->data_was_written = FALSE;

   return mxml_write_line(writer, line) == (int)strlen(line);
}
