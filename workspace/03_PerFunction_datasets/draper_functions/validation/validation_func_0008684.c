gdu_create_filesystem_widget_get_property (GObject    *object,
                                           guint       property_id,
                                           GValue     *value,
                                           GParamSpec *pspec)
{
  GduCreateFilesystemWidget *widget = GDU_CREATE_FILESYSTEM_WIDGET (object);

  switch (property_id)
    {
    case PROP_APPLICATION:
      g_value_set_object (value, widget->application);
      break;

    case PROP_DRIVE:
      g_value_set_object (value, widget->drive);
      break;

    case PROP_ADDITIONAL_FSTYPES:
      g_value_set_boxed (value, widget->additional_fstypes);
      break;

    case PROP_FSTYPE:
      g_value_set_string (value, widget->fstype);
      break;

    case PROP_NAME:
      g_value_set_string (value, widget->name);
      break;

    case PROP_PASSPHRASE:
      g_value_set_string (value, widget->passphrase);
      break;

    case PROP_HAS_INFO:
      g_value_set_boolean (value, widget->has_info);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}
