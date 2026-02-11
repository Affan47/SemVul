binary_payload_start(CELL pointer)
{
	F_TUPLE *tuple;
	F_TUPLE_LAYOUT *layout;

	switch(untag_header(get(pointer)))
	{

	case FLOAT_TYPE:
	case BYTE_ARRAY_TYPE:
	case BIGNUM_TYPE:
	case CALLSTACK_TYPE:
		return 0;

	case WORD_TYPE:
		return sizeof(F_WORD) - CELLS * 3;
	case ALIEN_TYPE:
		return CELLS * 3;
	case DLL_TYPE:
		return CELLS * 2;
	case QUOTATION_TYPE:
		return sizeof(F_QUOTATION) - CELLS * 2;
	case STRING_TYPE:
		return sizeof(F_STRING);

	case ARRAY_TYPE:
		return array_size(array_capacity((F_ARRAY*)pointer));
	case TUPLE_TYPE:
		tuple = untag_object(pointer);
		layout = untag_object(tuple->layout);
		return tuple_size(layout);
	case RATIO_TYPE:
		return sizeof(F_RATIO);
	case COMPLEX_TYPE:
		return sizeof(F_COMPLEX);
	case WRAPPER_TYPE:
		return sizeof(F_WRAPPER);
	default:
		critical_error("Invalid header",pointer);
		return -1;
	}
}
