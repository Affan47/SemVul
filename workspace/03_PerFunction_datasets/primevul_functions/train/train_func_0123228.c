uint64 EbmlElementSize(uint64 type, const char* value) {
  if (!value)
    return 0;


  uint64 ebml_size = GetUIntSize(type);


  ebml_size += strlen(value);


  ebml_size += GetCodedUIntSize(strlen(value));

  return ebml_size;
}
