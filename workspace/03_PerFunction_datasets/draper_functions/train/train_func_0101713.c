get_object_types (void)
{
    gpointer g_object_class;
    gint i = 0;
    object_types[i++] = g_udev_device_type_get_type ();
    object_types[i++] = g_udev_device_get_type ();
    object_types[i++] = g_udev_client_get_type ();
    object_types[i++] = g_udev_enumerator_get_type ();
    object_types[i] = 0;


    g_object_class = g_type_class_ref (G_TYPE_OBJECT);


    for (i=0; object_types[i]; i++)
      {
        if (G_TYPE_IS_CLASSED (object_types[i]))
          g_type_class_ref (object_types[i]);
        if (G_TYPE_IS_INTERFACE (object_types[i]))
          g_type_default_interface_ref (object_types[i]);
      }

    g_type_class_unref (g_object_class);

    return object_types;
}
