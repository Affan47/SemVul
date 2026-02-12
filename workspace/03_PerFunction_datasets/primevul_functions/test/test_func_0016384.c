const char* InstanceKlass::signature_name() const {
  int hash_len = 0;
  char hash_buf[40];


  if (is_anonymous()) {
    intptr_t hash = (java_mirror() != NULL) ? java_mirror()->identity_hash() : 0;
    jio_snprintf(hash_buf, sizeof(hash_buf), "/" UINTX_FORMAT, (uintx)hash);
    hash_len = (int)strlen(hash_buf);
  }


  const char* src = (const char*) (name()->as_C_string());
  const int src_length = (int)strlen(src);

  char* dest = NEW_RESOURCE_ARRAY(char, src_length + hash_len + 3);


  int dest_index = 0;
  dest[dest_index++] = 'L';


  for (int src_index = 0; src_index < src_length; ) {
    dest[dest_index++] = src[src_index++];
  }


  for (int hash_index = 0; hash_index < hash_len; ) {
    dest[dest_index++] = hash_buf[hash_index++];
  }


  dest[dest_index++] = ';';
  dest[dest_index] = '\0';
  return dest;
}
