uint64 EbmlElementSize(uint64 type, uint64 value, uint64 fixed_size) {

  uint64 ebml_size = GetUIntSize(type);


  ebml_size += (fixed_size > 0) ? fixed_size : GetUIntSize(value);


  ebml_size++;

  return ebml_size;
}
