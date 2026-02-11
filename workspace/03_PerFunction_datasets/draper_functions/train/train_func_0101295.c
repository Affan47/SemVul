ur_addr_map_put(ur_addr_map* map, ioa_addr* key, ur_addr_map_value_type value) {

  if(!ur_addr_map_valid(map)) return -1;

  else {

    addr_list_header* slh = get_addr_list_header(map, key);

    addr_elem* elem = addr_list_get(slh, key);
    if(elem) {
      elem->value=value;
    } else {
      addr_list_add(slh,key,value);
    }

    return 0;
  }
}
