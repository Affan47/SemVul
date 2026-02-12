raptor_xml_writer_write_xml_declaration(raptor_xml_writer* xml_writer)
{
  if(!xml_writer->xml_declaration_checked) {

    xml_writer->xml_declaration_checked = 1;

    if(RAPTOR_OPTIONS_GET_NUMERIC(xml_writer,
                                  RAPTOR_OPTION_WRITER_XML_DECLARATION)) {
      raptor_iostream_string_write((const unsigned char*)"<?xml version=\"",
                                   xml_writer->iostr);
      raptor_iostream_counted_string_write((XML_WRITER_XML_VERSION(xml_writer) == 10) ?
                                           (const unsigned char*)"1.0" :
                                           (const unsigned char*)"1.1",
                                           3, xml_writer->iostr);
      raptor_iostream_string_write((const unsigned char*)"\" encoding=\"utf-8\"?>\n",
                                   xml_writer->iostr);
    }
  }

}
