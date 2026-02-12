static zval* to_zval_union(encodeTypePtr enc, xmlNodePtr data TSRMLS_DC) {

	return to_zval_list(enc, data TSRMLS_CC);
}
