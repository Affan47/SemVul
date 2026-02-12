uint64 EbmlDateElementSize(uint64 type) {

  uint64 ebml_size = GetUIntSize(type);


  ebml_size += kDateElementSize;


  ebml_size++;

  return ebml_size;
}
