int ndpi_load_category(struct ndpi_detection_module_struct *ndpi_struct, const char *ip_or_name,
                       ndpi_protocol_category_t category) {
  int rv;


  rv = ndpi_load_ip_category(ndpi_struct, ip_or_name, category);

  if(rv < 0) {

    rv = ndpi_load_hostname_category(ndpi_struct, ip_or_name, category);
  }

  return(rv);
}
