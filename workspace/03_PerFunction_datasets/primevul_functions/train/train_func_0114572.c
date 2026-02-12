static PHP_INI_MH(OnUpdateTimeout)
{
	if (stage==PHP_INI_STAGE_STARTUP) {

		ZEND_ATOL(EG(timeout_seconds), ZSTR_VAL(new_value));
		return SUCCESS;
	}
	zend_unset_timeout();
	ZEND_ATOL(EG(timeout_seconds), ZSTR_VAL(new_value));
	zend_set_timeout(EG(timeout_seconds), 0);
	return SUCCESS;
}
