gth_test_simple_get_property (GObject    *object,
			      guint       property_id,
			      GValue     *value,
			      GParamSpec *pspec)
{
	GthTestSimple *test;

        test = GTH_TEST_SIMPLE (object);

	switch (property_id) {
	case PROP_DATA_TYPE:
		g_value_set_enum (value, test->priv->data_type);
		break;

	case PROP_DATA_AS_STRING:
		g_value_set_string (value, test->priv->data.s);
		break;

	case PROP_DATA_AS_INT:
		g_value_set_int (value, test->priv->data.i);
		break;

	case PROP_DATA_AS_DATE:
		g_value_set_boxed (value, test->priv->data.date);
		break;

	case PROP_GET_DATA:
		g_value_set_pointer (value, test->priv->get_data);
		break;

	case PROP_OP:
		g_value_set_enum (value, test->priv->op);
		break;

	case PROP_NEGATIVE:
		g_value_set_boolean (value, test->priv->negative);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
