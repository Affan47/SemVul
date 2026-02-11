lff_read (lff_t * lff, void * data) {
  if (lff->read_index == lff->write_index) {
    return -1;
  } else {
    memcpy (data, ((char *)lff->data) + (lff->read_index * lff->object_size),
            lff->object_size);
    lff->read_index++;
    if (lff->read_index >= lff->size) {
      lff->read_index = 0;
    }
    return 0;
  }
}
