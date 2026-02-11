build_parameters_string (GStrv parameters)
{
  GPtrArray *output = g_ptr_array_new ();
  char *join;
  GStrv iter;

  for (iter = parameters; iter != NULL && *iter != NULL; iter++)
    {
      static const char *prefix = "type=";
      const char *param = *iter;
      InfoParameterData *iter2;

      if (!g_str_has_prefix (param, prefix))
        continue;

      param += strlen (prefix);

      for (iter2 = info_parameter_data; iter2->type != NULL; iter2++)
        {
          if (!tp_strdiff (iter2->type, param))
            {
              g_ptr_array_add (output, gettext (iter2->title));
              break;
            }
        }
    }

  if (output->len == 0)
    return NULL;

  g_ptr_array_add (output, NULL);

  join = g_strjoinv (", ", (char **) output->pdata);
  g_ptr_array_unref (output);

  return join;
}
