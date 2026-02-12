static int hton_ext_based_table_discovery(handlerton *hton, LEX_CSTRING *db,
                             MY_DIR *dir, handlerton::discovered_list *result)
{


  return extension_based_table_discovery(dir, hton->tablefile_extensions[0],
                                         result);
}
