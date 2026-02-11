get_cwidth(CS_DATAFMT *column) {
	CS_INT len;

	switch ((int) column->datatype) {
	case CS_CHAR_TYPE:
	case CS_LONGCHAR_TYPE:
	case CS_VARCHAR_TYPE:
	case CS_TEXT_TYPE:
	case CS_IMAGE_TYPE:
        len = column->maxlength;
		break;

	case CS_BINARY_TYPE:
	case CS_VARBINARY_TYPE:
	case CS_LONGBINARY_TYPE:


		len = (2 * column->maxlength) + 2;
		break;

	case CS_BIT_TYPE:
	case CS_TINYINT_TYPE:
		len = 3;
		break;

	case CS_SMALLINT_TYPE:
#if defined(CS_USMALLINT_TYPE)
	case CS_USMALLINT_TYPE:
#endif
		len = 6;
		break;

	case CS_INT_TYPE:
#if defined(CS_UINT_TYPE)
	case CS_UINT_TYPE:
#endif
		len = 11;
		break;

#if defined(CS_BIGINT_TYPE)
	case CS_BIGINT_TYPE:
	case CS_UBIGINT_TYPE:
		len = 22;
#endif

	case CS_REAL_TYPE:
	case CS_FLOAT_TYPE:
		len = 20;
		break;

	case CS_MONEY_TYPE:
	case CS_MONEY4_TYPE:
		len = 24;
		break;

	case CS_DATETIME_TYPE:
	case CS_DATETIME4_TYPE:
#if defined(CS_DATE_TYPE)
	case CS_DATE_TYPE:
	case CS_TIME_TYPE:
#endif
#if defined(CS_BIGDATETIME_TYPE)
	case CS_BIGDATETIME_TYPE:
	case CS_BIGTIME_TYPE:
#endif
		len = 40;
		break;

#ifdef CS_UNIQUE_TYPE
		case CS_UNIQUE_TYPE:
		len = 40;
		break;
#endif

	default:
		len = column->maxlength;
		break;
	}

	return len;
}
