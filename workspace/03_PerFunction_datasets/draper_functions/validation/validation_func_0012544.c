start_member (GMarkupParseContext *context,
	      const gchar         *element_name,
	      const gchar        **attribute_names,
	      const gchar        **attribute_values,
	      ParseContext        *ctx,
	      GError             **error)
{
  const gchar *name;
  const gchar *value;
  const gchar *deprecated;
  const gchar *c_identifier;
  GIrNodeEnum *enum_;
  GIrNodeValue *value_;

  if (!(strcmp (element_name, "member") == 0 &&
	ctx->state == STATE_ENUM))
    return FALSE;

  name = find_attribute ("name", attribute_names, attribute_values);
  value = find_attribute ("value", attribute_names, attribute_values);
  deprecated = find_attribute ("deprecated", attribute_names, attribute_values);
  c_identifier = find_attribute ("c:identifier", attribute_names, attribute_values);

  if (name == NULL)
    {
      MISSING_ATTRIBUTE (context, error, element_name, "name");
      return FALSE;
    }

  value_ = (GIrNodeValue *) _g_ir_node_new (G_IR_NODE_VALUE,
					   ctx->current_module);

  ((GIrNode *)value_)->name = g_strdup (name);

  value_->value = parse_value (value);

  if (deprecated)
    value_->deprecated = TRUE;
  else
    value_->deprecated = FALSE;

  g_hash_table_insert (((GIrNode *)value_)->attributes,
                       g_strdup ("c:identifier"),
                       g_strdup (c_identifier));

  enum_ = (GIrNodeEnum *)CURRENT_NODE (ctx);
  enum_->values = g_list_append (enum_->values, value_);

  return TRUE;
}
