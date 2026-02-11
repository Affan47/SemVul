zend_check_property_access(zend_object *zobj, const char *prop_info_name, int prop_info_name_len TSRMLS_DC)
{
	zend_property_info *property_info;
	const char *class_name, *prop_name;
	zval member;

	zend_unmangle_property_name(prop_info_name, prop_info_name_len, &class_name, &prop_name);
	ZVAL_STRING(&member, prop_name, 0);
	property_info = zend_get_property_info_quick(zobj->ce, &member, 1, NULL TSRMLS_CC);
	if (!property_info) {
		return FAILURE;
	}
	if (class_name && class_name[0] != '*') {
		if (!(property_info->flags & ZEND_ACC_PRIVATE)) {

			return FAILURE;
		} else if (strcmp(prop_info_name+1, property_info->name+1)) {

			return FAILURE;
		}
	}
	return zend_verify_property_access(property_info, zobj->ce TSRMLS_CC) ? SUCCESS : FAILURE;
}
