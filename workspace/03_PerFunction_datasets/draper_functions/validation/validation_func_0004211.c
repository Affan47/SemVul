midgard_query_constraint_set_operator (MidgardQueryConstraint *self, const gchar *op)
{
	g_return_val_if_fail (self != NULL, FALSE);

 	GdaSqlOperatorType op_type;
	if (!__query_constraint_operator_is_valid (op, &op_type))
		return FALSE;

        self->priv->op = g_strdup (op);
        self->priv->op_type = op_type;
	return TRUE;
}
