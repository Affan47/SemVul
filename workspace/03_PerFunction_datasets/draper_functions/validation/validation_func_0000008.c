remap_nscd_areas(Area remap_nscd_areas_array[],
			     int  num_remap_nscd_areas) {
  Area *area;
  for (area = remap_nscd_areas_array; num_remap_nscd_areas-- > 0; area++) {
    if (area->flags == END_OF_NSCD_AREAS) {
      MTCP_PRINTF("Too many NSCD areas to remap.\n");
      mtcp_abort();
    }
    if ( munmap(area->addr, area->size) == -1) {
      MTCP_PRINTF("error unmapping NSCD shared area: %s\n",
                  strerror(mtcp_sys_errno));
      mtcp_abort();
    }
    if (mmap(area->addr, area->size, area->prot, area->flags, 0, 0)
        == MAP_FAILED) {
      MTCP_PRINTF("error remapping NSCD shared area: %s\n", strerror(errno));
      mtcp_abort();
    }
    memset(area->addr, 0, area->size);
  }
}
