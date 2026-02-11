se_prop_set_int (se_t *se, se_o_t *o, const char *id, int value)
{
  se_prop_t *p;

  if (!o)
    o = se->g;

  p = se_prop_find (se, o, id);
  if (p)
  {
    se_prop_read_t v;
    if (p->reader && p->se_type != SE_TYPE_INT)
    {
      g_printerr (_("script_engine: se_prop_set%s: can't change type of property %s\n"),
	       "_int", se_id (se, o, id));
      return;
    }
    free (p->value);
    p->value = g_strdup_printf ("%d", v.i = value);
    p->se_type = SE_TYPE_INT;
    se_prop_listeners (se, o, p, v);
  }
  else
    se_prop_create_int (se, o, id, value, FALSE);
}
