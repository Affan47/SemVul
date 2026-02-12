static int hash_zval_identical_function(zval *z1, zval *z2)
{


	ZVAL_DEREF(z1);
	ZVAL_DEREF(z2);
	return fast_is_not_identical_function(z1, z2);
}
