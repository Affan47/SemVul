gda_postgres_provider_get_default_dbms_type (GdaServerProvider *provider, GdaConnection *cnc, GType type)
{
	if (cnc) {
		g_return_val_if_fail (GDA_IS_CONNECTION (cnc), NULL);
		g_return_val_if_fail (gda_connection_get_provider (cnc) == provider, NULL);
	}

	if (type == G_TYPE_INT64)
                return "int8";
        if (type == G_TYPE_UINT64)
                return "int8";
        if (type == GDA_TYPE_BINARY)
                return "bytea";
        if (type == GDA_TYPE_BLOB)
                return "oid";
        if (type == G_TYPE_BOOLEAN)
                return "bool";
        if (type == G_TYPE_DATE)
                return "date";
        if (type == G_TYPE_DOUBLE)
                return "float8";
        if (type == GDA_TYPE_GEOMETRIC_POINT)
                return "point";
        if (type == G_TYPE_OBJECT)
                return "text";
        if (type == G_TYPE_INT)
                return "int4";
        if (type == GDA_TYPE_NUMERIC)
                return "numeric";
        if (type == G_TYPE_FLOAT)
                return "float4";
        if (type == GDA_TYPE_SHORT)
                return "int2";
        if (type == GDA_TYPE_USHORT)
                return "int2";
        if (type == G_TYPE_STRING)
                return "varchar";
        if (type == GDA_TYPE_TIME)
                return "time";
        if (type == GDA_TYPE_TIMESTAMP)
                return "timestamp";
        if (type == G_TYPE_CHAR)
                return "smallint";
        if (type == G_TYPE_UCHAR)
                return "smallint";
        if (type == G_TYPE_ULONG)
                return "int8";
        if (type == G_TYPE_GTYPE)
                return "varchar";
        if (type == G_TYPE_UINT)
                return "int4";

	if ((type == GDA_TYPE_NULL) ||
	    (type == G_TYPE_GTYPE))
		return NULL;

        return "text";
}
