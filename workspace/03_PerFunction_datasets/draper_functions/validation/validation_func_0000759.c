garcon_menu_directory_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  GarconMenuDirectory *directory = GARCON_MENU_DIRECTORY (object);

  switch (prop_id)
    {
    case PROP_FILE:
      directory->priv->file = g_value_dup_object (value);
      break;

    case PROP_NAME:
      garcon_menu_directory_set_name (directory, g_value_get_string (value));
      break;

    case PROP_COMMENT:
      garcon_menu_directory_set_comment (directory, g_value_get_string (value));
      break;

    case PROP_ICON_NAME:
      garcon_menu_directory_set_icon_name (directory, g_value_get_string (value));
      break;

    case PROP_NO_DISPLAY:
      garcon_menu_directory_set_no_display (directory, g_value_get_boolean (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
