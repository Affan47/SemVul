get_store(listtype_t listtype)
{
  if (listtype == HD_LIST)
    return transfer_widgets.hdliststore;
  else if (listtype == JB_LIST)
    return transfer_widgets.jbliststore;
  else if (listtype == HDDATA_LIST)
    return data_widgets.hdliststore;
  else if (listtype == JBDATA_LIST)
    return data_widgets.jbliststore;
  else
    return NULL;
}
