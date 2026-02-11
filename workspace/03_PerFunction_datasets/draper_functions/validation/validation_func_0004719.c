cb_xml_to_vfs (GsfOutput *output, const guint8* buf, int nb)
{
	if (start) {
		char const *end = strchr (reinterpret_cast <char const *> (buf), '\n');
		gsf_output_write (output, 40, reinterpret_cast <guint8 const *> ("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"));
		gsf_output_write (output, 70, reinterpret_cast <guint8 const *> ("<!DOCTYPE CDXML SYSTEM \"http://www.cambridgesoft.com/xml/cdxml.dtd\" >\n"));
		start = false;
		return gsf_output_write (output, strlen (end) - 1, reinterpret_cast <guint8 const *> (end + 1))? nb: 0;
	} else
		return gsf_output_write (output, nb, buf)? nb: 0;
}
