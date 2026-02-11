gconf_engine_get_string(GConfEngine* conf, const gchar* key,
                 GError** err)
{
  GConfValue* val;
  static const gchar* deflt = NULL;

  g_return_val_if_fail(conf != NULL, NULL);
  g_return_val_if_fail(key != NULL, NULL);

  val = gconf_engine_get (conf, key, err);

  if (val == NULL)
    return g_strdup(deflt);
  else
    {
      gchar* retval;

      if (val->type != GCONF_VALUE_STRING)
        {
          if (err)
            *err = gconf_error_new(GCONF_ERROR_TYPE_MISMATCH, _("Expected string, got %s"),
                                    gconf_value_type_to_string(val->type));
          gconf_value_free(val);
          return g_strdup(deflt);
        }

      retval = gconf_value_steal_string (val);
      gconf_value_free (val);

      return retval;
    }
}
