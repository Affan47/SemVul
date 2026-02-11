fs_codec_add_feedback_parameter (FsCodec *codec, const gchar *type,
    const gchar *subtype, const gchar *extra_params)
{
  FsFeedbackParameter *param;

  g_return_if_fail (type != NULL);
  g_return_if_fail (subtype != NULL);
  g_return_if_fail (extra_params != NULL);

  param = g_slice_new (FsFeedbackParameter);

  param->type = g_strdup (type);
  param->subtype = g_strdup (subtype);
  param->extra_params = g_strdup (extra_params);

  codec->feedback_params = g_list_append (codec->feedback_params, param);
}
