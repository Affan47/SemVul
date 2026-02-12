uint64 EbmlElementSize(uint64 type, float ) {

  uint64 ebml_size = GetUIntSize(type);


  ebml_size += sizeof(float);


  ebml_size++;

  return ebml_size;
}
