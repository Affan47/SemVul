__exif_tag_capturing_contrast_sharpness_to_exif_value (const gchar * str,
    const gchar * tag_name)
{
  if (str == NULL)
    goto end;

  if (strcmp (str, "normal") == 0)
    return 0;
  else if (strcmp (str, "soft") == 0)
    return 1;
  else if (strcmp (str, "hard") == 0)
    return 2;

end:
  GST_WARNING ("Invalid %s type: %s", tag_name, str);
  return -1;
}
