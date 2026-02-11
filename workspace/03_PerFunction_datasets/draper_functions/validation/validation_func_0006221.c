read_sysfs_attr_as_uint64 (GUdevDevice *device,
                           const gchar *attr)
{
  guint64 ret = 0;
  gchar *str = NULL;

  str = read_sysfs_attr (device, attr);
  if (str == NULL)
    goto out;

  ret = atoll (str);
  g_free (str);

 out:
  return ret;
}
