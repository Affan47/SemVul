sxe_count_elements(zval *object, long *count TSRMLS_DC)
{
	php_sxe_object  *intern;
	intern = php_sxe_fetch_object(object TSRMLS_CC);
	if (intern->fptr_count) {
		zval *rv;
		zend_call_method_with_0_params(&object, intern->zo.ce, &intern->fptr_count, "count", &rv);
		if (rv) {
			if (intern->tmp) {
				zval_ptr_dtor(&intern->tmp);
			}
			MAKE_STD_ZVAL(intern->tmp);
			ZVAL_ZVAL(intern->tmp, rv, 1, 1);
			convert_to_long(intern->tmp);
			*count = (long) Z_LVAL_P(intern->tmp);
			return SUCCESS;
		}
		return FAILURE;
	}
	return php_sxe_count_elements_helper(intern, count TSRMLS_CC);
}
