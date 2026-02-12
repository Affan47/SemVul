static struct Curl_sh_entry *sh_addentry(struct curl_hash *sh,
                                         curl_socket_t s,
                                         struct Curl_easy *data)
{
  struct Curl_sh_entry *there = sh_getentry(sh, s);
  struct Curl_sh_entry *check;

  if(there)

    return there;


  check = calloc(1, sizeof(struct Curl_sh_entry));
  if(!check)
    return NULL;

  check->easy = data;
  check->socket = s;


  if(!Curl_hash_add(sh, (char *)&s, sizeof(curl_socket_t), check)) {
    free(check);
    return NULL;
  }

  return check;
}
