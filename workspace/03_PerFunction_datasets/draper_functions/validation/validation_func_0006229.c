send_xml_dialog (pixma_t * s, const char * xml_message)
{
  mp810_t *mp = (mp810_t *) s->subdriver;
  int datalen;

  datalen = pixma_cmd_transaction (s, xml_message, strlen (xml_message),
                                   mp->cb.buf, 1024);
  if (datalen < 0)
    return datalen;

  mp->cb.buf[datalen] = 0;

  PDBG (pixma_dbg (10, "XML message sent to scanner:\n%s\n", xml_message));
  PDBG (pixma_dbg (10, "XML response back from scanner:\n%s\n", mp->cb.buf));

  return (strcasestr ((const char *) mp->cb.buf, XML_OK) != NULL);
}
