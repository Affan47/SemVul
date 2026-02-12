static zval* to_zval_list(encodeTypePtr enc, xmlNodePtr data TSRMLS_DC) {

	return to_zval_stringc(enc, data TSRMLS_CC);
}
