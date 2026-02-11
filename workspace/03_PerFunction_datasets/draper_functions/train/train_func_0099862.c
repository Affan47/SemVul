_gtk_marshal_OBJECT__VOIDv (GClosure     *closure,
                            GValue       *return_value,
                            gpointer      instance,
                            va_list       args,
                            gpointer      marshal_data,
                            int           n_params,
                            GType        *param_types)
{
  typedef GObject* (*GMarshalFunc_OBJECT__VOID) (gpointer     instance,
                                                 gpointer     data);
  GCClosure *cc = (GCClosure*) closure;
  gpointer data1, data2;
  GMarshalFunc_OBJECT__VOID callback;
  GObject* v_return;

  g_return_if_fail (return_value != NULL);

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
  callback = (GMarshalFunc_OBJECT__VOID) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       data2);

  g_value_take_object (return_value, v_return);
}
