uint64 EbmlMasterElementSize(uint64 type, uint64 value) {

  int32 ebml_size = GetUIntSize(type);


  ebml_size += GetCodedUIntSize(value);

  return ebml_size;
}
