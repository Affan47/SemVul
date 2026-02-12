uint64 EbmlElementSize(uint64 type, int64 value) {

  int32 ebml_size = GetUIntSize(type);


  ebml_size += GetIntSize(value);


  ebml_size++;

  return ebml_size;
}
