raptor_xml_writer_start_element(raptor_xml_writer* xml_writer,
                                raptor_xml_element *element)
{
  raptor_xml_writer_write_xml_declaration(xml_writer);

  XML_WRITER_FLUSH_CLOSE_BRACKET(xml_writer);

  if(xml_writer->pending_newline || XML_WRITER_AUTO_INDENT(xml_writer))
    raptor_xml_writer_indent(xml_writer);

  raptor_xml_writer_start_element_common(xml_writer, element,
                                         XML_WRITER_AUTO_EMPTY(xml_writer));

  xml_writer->depth++;


  if(xml_writer->current_element)
    element->parent = xml_writer->current_element;

  xml_writer->current_element = element;
  if(element->parent)
    element->parent->content_element_seen = 1;
}
