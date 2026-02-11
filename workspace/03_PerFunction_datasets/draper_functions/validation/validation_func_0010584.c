ur_string_map_size(const ur_string_map* map) {
  if(ur_string_map_valid(map)) {
    size_t ret=0;
    int i=0;
    for(i=0;i<STRING_MAP_SIZE;i++) {
      ret+=string_list_size(map->lists[i].list);
    }
    return ret;
  } else {
    return 0;
  }
}
