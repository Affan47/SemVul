_gtk_marshal_OBJECT__OBJECT_INT_INTv (GClosure     *closure,
                                      GValue       *return_value,
                                      gpointer      instance,
                                      va_list       args,
                                      gpointer      marshal_data,
                                      int           n_params,
                                      GType        *param_types)
{
  typedef GObject* (*GMarshalFunc_OBJECT__OBJECT_INT_INT) (gpointer     instance,
                                                           gpointer     arg_0,
                                                           gint         arg_1,
                                                           gint         arg_2,
                                                           gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_OBJECT__OBJECT_INT_INT callback;
  gpointer arg0;
  gint arg1;
  gint arg2;
  va_list args_copy;
  GObject* v_return;

  g_return_if_fail (return_value != NULL);

  G_VA_COPY (args_copy, args);
  arg0 = (gpointer) va_arg (args_copy, gpointer);
  if (arg0 != NULL)
    arg0 = g_object_ref (arg0);
  arg1 = (gint) va_arg (args_copy, gint);
  arg2 = (gint) va_arg (args_copy, gint);
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
  callback = (GMarshalFunc_OBJECT__OBJECT_INT_INT) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       arg0,
                       arg1,
                       arg2,
                       data2);
  if (arg0 != NULL)
    g_object_unref (arg0);

  g_value_take_object (return_value, v_return);
}
