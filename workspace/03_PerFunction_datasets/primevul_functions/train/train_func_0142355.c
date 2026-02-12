static xmlNodePtr to_xml_list1(encodeTypePtr enc, zval *data, int style, xmlNodePtr parent TSRMLS_DC) {

	return to_xml_list(enc,data,style, parent TSRMLS_CC);
}
