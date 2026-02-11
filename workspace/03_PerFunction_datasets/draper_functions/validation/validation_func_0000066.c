register_pci_state(bx_list_c *list, Bit8u *pci_conf)
{
  char name[6];

  bx_list_c *pci = new bx_list_c(list, "pci_conf", 256);
  for (unsigned i=0; i<256; i++) {
    sprintf(name, "0x%02x", i);
    new bx_shadow_num_c(pci, name, &pci_conf[i], BASE_HEX);
  }
}
