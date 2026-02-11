osm_feature_symbol(const int ikey, const char* value)
{
  char* result;
  char buff[128];
  osm_icon_mapping_t* data;

  buff[0] = ikey;
  strncpy(&buff[1], value, sizeof(buff) - 1);

  if (avltree_find(values, buff, (const void**)&data)) {
    result = xstrdup(data->icon);
  } else {
    xasprintf(&result, "%s:%s", osm_features[ikey], value);
  }

  return result;
}
