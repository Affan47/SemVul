mcnet_metadata_generator_size(mcnet_metadata_t* metadata) {
  size_t res = 0;

  int i;
  for (i = 0; i < metadata->count; ++i) {
    res += 1;

    if (metadata->entries[i] == NULL) {
      return MCNET_EINVALID;
    }

    switch (metadata->entries[i]->type) {
      case MCNET_METADATA_TYPE_BYTE: {
        res += 1;
        break;
      }
      case MCNET_METADATA_TYPE_SHORT: {
        res += 2;
        break;
      }
      case MCNET_METADATA_TYPE_INT: {
        res += 4;
        break;
      }
      case MCNET_METADATA_TYPE_FLOAT: {
        res += 4;
        break;
      }
      case MCNET_METADATA_TYPE_STRING16: {
        mcnet_metadata_entry_string16_t* _entry = (mcnet_metadata_entry_string16_t*)(metadata->entries[i]);
        res += 2;
        res += _entry->data_length;
        break;
      }
      case MCNET_METADATA_TYPE_SLOT: {
        res += 5;
        break;
      }
      case MCNET_METADATA_TYPE_INTS: {
        res += 12;
        break;
      }
    }
  }

  res += 1;

  return res;
}
