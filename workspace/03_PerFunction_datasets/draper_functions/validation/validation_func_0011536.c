connect_accel_group (OOP accel_group,
                     guint accel_key,
                     GdkModifierType accel_mods,
                     GtkAccelFlags accel_flags,
                     OOP receiver,
                     OOP selector,
		     OOP user_data)
{
  GtkAccelGroup *cObject = _gst_vm_proxy->OOPToCObject (accel_group);
  int n_params;
  GClosure *closure;
  OOP oop_sel_args;

  oop_sel_args = _gst_vm_proxy->strMsgSend (selector, "numArgs", NULL);
  if (oop_sel_args == _gst_vm_proxy->nilOOP)
    return (-3);


  n_params = _gst_vm_proxy->OOPToInt (oop_sel_args);
  if (n_params > 4)
    return (-4);


  accel_group = narrow_oop_for_g_object (G_OBJECT (cObject), accel_group);

  closure = create_smalltalk_closure (receiver, selector, NULL,
                                      accel_group, n_params);
  gtk_accel_group_connect (cObject, accel_key, accel_mods, accel_flags, closure);
  return 0;
}
