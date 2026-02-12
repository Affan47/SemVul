static xmlNodePtr guess_xml_convert(encodeTypePtr type, zval *data, int style, xmlNodePtr parent TSRMLS_DC)
{
	encodePtr  enc;
	xmlNodePtr ret;

	if (data) {
		enc = get_conversion(data->type);
	} else {
		enc = get_conversion(IS_NULL);
	}
	ret = master_to_xml_int(enc, data, style, parent, 0 TSRMLS_CC);


	return ret;
}
