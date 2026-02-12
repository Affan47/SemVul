static xmlNodePtr to_xml_duration(encodeTypePtr type, zval *data, int style, xmlNodePtr parent TSRMLS_DC)
{

	return to_xml_string(type, data, style, parent TSRMLS_CC);
}
