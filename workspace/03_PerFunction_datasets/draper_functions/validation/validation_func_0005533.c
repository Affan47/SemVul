id_info_free(id_info *info)
{
  Tcl_HashEntry *entry;
  Tcl_HashSearch search;


  entry = Tcl_FirstHashEntry(&info->doc_hash_byid, &search);
  while (entry) {
    doc_info *d_info;

    d_info = (doc_info *)Tcl_GetHashValue(entry);
    doc_info_free(info, d_info);
    entry = Tcl_NextHashEntry(&search);
  }
  Tcl_DeleteHashTable(&info->doc_hash_byid);


  Tcl_DeleteHashTable(&info->doc_hash_bydoc);


  entry = Tcl_FirstHashEntry(&info->node_hash_bynode, &search);
  while (entry) {
    Ns_Free(Tcl_GetHashValue(entry));
    entry = Tcl_NextHashEntry(&search);
  }
  Tcl_DeleteHashTable(&info->node_hash_bynode);


  Tcl_DeleteHashTable(&info->node_hash_byid);
  Ns_Free(info);
}
