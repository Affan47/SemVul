zval *sdl_guess_convert_zval(encodeTypePtr enc, xmlNodePtr data TSRMLS_DC)
{
	sdlTypePtr type;

	type = enc->sdl_type;
	if (type == NULL) {
		return guess_zval_convert(enc, data TSRMLS_CC);
	}


	switch (type->kind) {
		case XSD_TYPEKIND_SIMPLE:
			if (type->encode && enc != &type->encode->details) {
				return master_to_zval_int(type->encode, data TSRMLS_CC);
			} else {
				return guess_zval_convert(enc, data TSRMLS_CC);
			}
			break;
		case XSD_TYPEKIND_LIST:
			return to_zval_list(enc, data TSRMLS_CC);
		case XSD_TYPEKIND_UNION:
			return to_zval_union(enc, data TSRMLS_CC);
		case XSD_TYPEKIND_COMPLEX:
		case XSD_TYPEKIND_RESTRICTION:
		case XSD_TYPEKIND_EXTENSION:
			if (type->encode &&
			    (type->encode->details.type == IS_ARRAY ||
			     type->encode->details.type == SOAP_ENC_ARRAY)) {
				return to_zval_array(enc, data TSRMLS_CC);
			}
			return to_zval_object(enc, data TSRMLS_CC);
		default:
	  	soap_error0(E_ERROR, "Encoding: Internal Error");
			return guess_zval_convert(enc, data TSRMLS_CC);
	}
}
