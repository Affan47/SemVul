_gda_marshal_VOID__SLIST (GClosure     *closure,
			  GValue       *return_value G_GNUC_UNUSED,
			  guint         n_param_values,
			  const GValue *param_values,
			  gpointer      invocation_hint G_GNUC_UNUSED,
			  gpointer      marshal_data)
{
	typedef void (*GMarshalFunc_VOID__SLIST) (gpointer     data1,
						  gpointer     arg_1,
						  gpointer     data2);
	register GMarshalFunc_VOID__SLIST callback;
	register GCClosure *cc = (GCClosure*) closure;
	register gpointer data1, data2;

	g_return_if_fail (n_param_values == 2);

	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = g_value_peek_pointer (param_values + 0);
	}
	else {
		data1 = g_value_peek_pointer (param_values + 0);
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__SLIST) (marshal_data ? marshal_data : cc->callback);

	callback (data1,
		  g_value_get_pointer (param_values + 1),
		  data2);
}
