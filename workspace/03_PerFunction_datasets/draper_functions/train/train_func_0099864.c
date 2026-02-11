get_property (GObject *object, guint prop_id,
	      GValue *value, GParamSpec *pspec)
{
	GtksharpValobj *valobj = GTKSHARP_VALOBJ (object);

	switch (prop_id) {
	case PROP_BOOLEAN:
		g_value_set_boolean (value, valobj->the_boolean);
		break;
	case PROP_INT:
		g_value_set_int (value, valobj->the_int);
		break;
	case PROP_UINT:
		g_value_set_uint (value, valobj->the_uint);
		break;
	case PROP_INT64:
		g_value_set_int64 (value, valobj->the_int64);
		break;
	case PROP_UINT64:
		g_value_set_uint64 (value, valobj->the_uint64);
		break;
	case PROP_UNICHAR:
		g_value_set_uint (value, (guint)valobj->the_unichar);
		break;
	case PROP_ENUM:
		g_value_set_enum (value, valobj->the_enum);
		break;
	case PROP_FLAGS:
		g_value_set_flags (value, valobj->the_flags);
		break;
	case PROP_FLOAT:
		g_value_set_float (value, valobj->the_float);
		break;
	case PROP_DOUBLE:
		g_value_set_double (value, valobj->the_double);
		break;
	case PROP_STRING:
		g_value_set_string (value, valobj->the_string);
		break;
	case PROP_BOXED:
		g_value_set_boxed (value, &valobj->the_rect);
		break;
	case PROP_POINTER:
		g_value_set_pointer (value, valobj->the_pointer);
		break;
	case PROP_OBJECT:
		g_value_set_object (value, valobj->the_object);
		break;
	default:
		break;
	}
}
