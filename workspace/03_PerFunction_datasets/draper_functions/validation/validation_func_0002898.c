ssh_hmac_type_to_string(enum ssh_hmac_e hmac_type)
{
  int i = 0;
  struct ssh_hmac_struct *ssh_hmactab = ssh_get_hmactab();
  while (ssh_hmactab[i].name && (ssh_hmactab[i].hmac_type != hmac_type)) {
    i++;
  }
  return ssh_hmactab[i].name;
}
