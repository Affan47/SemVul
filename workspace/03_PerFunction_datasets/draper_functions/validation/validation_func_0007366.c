_midgard_sql_query_result_get_rows (MidgardQueryResult *result, guint *n_objects, GError **error)
{
	MidgardSqlQueryResult *self = MIDGARD_SQL_QUERY_RESULT (result);
        GError *err = NULL;
               _propagate_rows (self, n_objects, &err);
               *n_objects = self->n_rows;
        if (self->rows == NULL) {
                 if (err)
			 g_propagate_error (error, err);
                return NULL;
        }


        guint i;
        MidgardSqlQueryRow **rows = g_new (MidgardSqlQueryRow *, self->n_rows);
        for (i = 0; i < self->n_rows; i++) {
		rows[i] = (MidgardSqlQueryRow *) g_object_ref (self->rows[i]);
	}

        return (MidgardQueryRow **) rows;
}
