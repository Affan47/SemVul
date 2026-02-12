static void sh_delentry(struct curl_hash *sh, curl_socket_t s)
{


  Curl_hash_delete(sh, (char *)&s, sizeof(curl_socket_t));
}
