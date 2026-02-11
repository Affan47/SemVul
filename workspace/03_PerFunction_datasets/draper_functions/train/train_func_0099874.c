_gtk_marshal_VOID__BOXED_BOXED_POINTERv (GClosure     *closure,
                                         GValue       *return_value,
                                         gpointer      instance,
                                         va_list       args,
                                         gpointer      marshal_data,
                                         int           n_params,
                                         GType        *param_types)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_POINTER) (gpointer     instance,
                                                          gpointer     arg_0,
                                                          gpointer     arg_1,
                                                          gpointer     arg_2,
                                                          gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_VOID__BOXED_BOXED_POINTER callback;
  gpointer arg0;
  gpointer arg1;
  gpointer arg2;
  va_list args_copy;

  G_VA_COPY (args_copy, args);
  arg0 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[0] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg0 != NULL)
    arg0 = g_boxed_copy (param_types[0] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg0);
  arg1 = (gpointer) va_arg (args_copy, gpointer);
  if ((param_types[1] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg1 != NULL)
    arg1 = g_boxed_copy (param_types[1] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg1);
  arg2 = (gpointer) va_arg (args_copy, gpointer);
  va_end (args_copy);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = instance;
    }
  else
    {
      data1 = instance;
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            arg0,
            arg1,
            arg2,
            data2);
  if ((param_types[0] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg0 != NULL)
    g_boxed_free (param_types[0] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg0);
  if ((param_types[1] & G_SIGNAL_TYPE_STATIC_SCOPE) == 0 && arg1 != NULL)
    g_boxed_free (param_types[1] & ~G_SIGNAL_TYPE_STATIC_SCOPE, arg1);
}
