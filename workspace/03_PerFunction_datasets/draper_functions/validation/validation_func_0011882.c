is_not_identical_function(zval *result, zval *op1, zval *op2 TSRMLS_DC)
{
	if (is_identical_function(result, op1, op2 TSRMLS_CC) == FAILURE) {
		return FAILURE;
	}
	Z_LVAL_P(result) = !Z_LVAL_P(result);
	return SUCCESS;
}
