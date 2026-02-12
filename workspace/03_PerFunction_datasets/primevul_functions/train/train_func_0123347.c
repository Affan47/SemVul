uint64 EbmlElementSize(uint64 type, const uint8* value, uint64 size) {
  if (!value)
    return 0;


  uint64 ebml_size = GetUIntSize(type);


  ebml_size += size;


  ebml_size += GetCodedUIntSize(size);

  return ebml_size;
}
