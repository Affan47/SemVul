reflection_free_objects_storage(void *object TSRMLS_DC)
{
	reflection_object *intern = (reflection_object *) object;
	parameter_reference *reference;

	if (intern->ptr) {
		switch (intern->ref_type) {
		case REF_TYPE_PARAMETER:
			reference = (parameter_reference*)intern->ptr;
			_free_function(reference->fptr TSRMLS_CC);
			efree(intern->ptr);
			break;
		case REF_TYPE_FUNCTION:
			_free_function(intern->ptr TSRMLS_CC);
			break;
		case REF_TYPE_PROPERTY:
			efree(intern->ptr);
			break;
		case REF_TYPE_OTHER:
			break;
		}
	}
	intern->ptr = NULL;
	if (intern->obj) {
		zval_ptr_dtor(&intern->obj);
	}
	zend_objects_free_object_storage(object TSRMLS_CC);
}
