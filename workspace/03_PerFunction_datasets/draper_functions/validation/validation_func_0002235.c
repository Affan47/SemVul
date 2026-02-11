VALUE_undo_variant(VALUE *value)
{
	static void *jump[16] = {
		&&__VOID, &&__BOOLEAN, &&__BYTE, &&__SHORT, &&__INTEGER, &&__LONG, &&__SINGLE, &&__FLOAT, &&__DATE,
		&&__STRING, &&__CSTRING, &&__POINTER, &&__VOID, &&__FUNCTION, &&__CLASS, &&__NULL
		};

	TYPE type = value->_variant.vtype;


	value->type = type;

	if (TYPE_is_object(type))
		goto __OBJECT;
	else
		goto *jump[type];

__BOOLEAN:

	value->_boolean.value = value->_variant.value._boolean ? -1 : 0;
	return;

__BYTE:

	value->_byte.value = value->_variant.value._byte;
	return;

__SHORT:

	value->_short.value = value->_variant.value._short;
	return;

__INTEGER:

	value->_integer.value = value->_variant.value._integer;
	return;

__LONG:

	value->_long.value = value->_variant.value._long;
	return;

__SINGLE:

	value->_single.value = value->_variant.value._single;
	return;

__FLOAT:

	value->_float.value = value->_variant.value._float;
	return;

__DATE:


	value->_date.date = value->_variant.value._date.date;
	value->_date.time = value->_variant.value._date.time;
	return;

__STRING:

	{
		char *str = value->_variant.value._string;

		value->type = T_STRING;
		value->_string.addr = str;
		value->_string.start = 0;
		value->_string.len = STRING_length(str);

		return;
	}

__CSTRING:

	{
		char *str = value->_variant.value._string;

		value->type = T_CSTRING;
		value->_string.addr = str;
		value->_string.start = 0;
		value->_string.len = strlen(str);

		return;
	}

__OBJECT:

	value->_object.object = value->_variant.value._object;
	return;

__POINTER:

	value->_pointer.value = value->_variant.value._pointer;
	return;

__CLASS:

	value->_class.class = value->_variant.value._object;
	value->_class.super = NULL;
	return;

__NULL:
	return;

__VOID:
__FUNCTION:

	ERROR_panic("Bad type (%d) for VALUE_undo_variant", type);
}
