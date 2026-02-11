ParseNextTypeField(istream &input)
{
	uint32_t type = ParseInteger(input);

	switch (type) {
	case COD_DEBUG_NONE_FIELD:
		break;

	case COD_DEBUG_BOOLEAN_FIELD:
		ParseBoolean(input);
		break;

	case COD_DEBUG_BYTE_FIELD:
		ParseByte(input);
		break;

	case COD_DEBUG_CHAR_FIELD:
		ParseChar(input);
		break;

	case COD_DEBUG_SHORT_FIELD:
		ParseShort(input);
		break;

	case COD_DEBUG_INT_FIELD:
		ParseInt(input);
		break;

	case COD_DEBUG_LONG_FIELD:
		ParseLong(input);
		break;

	case COD_DEBUG_CLASS_FIELD:
		ParseClass(input);
		break;

	case COD_DEBUG_ARRAY_FIELD:
		ParseArray(input);
		break;

	case COD_DEBUG_VOID_FIELD:
		ParseVoid(input);
		break;

	case COD_DEBUG_DOUBLE_FIELD:
		ParseDouble(input);
		break;

	default:
		dout("Type unknown ! " << hex << type);
		type = 0xFFFFFFFF;
	}

	return type;
}
