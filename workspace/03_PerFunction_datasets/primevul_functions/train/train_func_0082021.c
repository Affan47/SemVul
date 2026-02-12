BYTE *DecompressRTF(variableLength *p, int *size) {
  BYTE *dst;
  BYTE *src;
  unsigned int in;
  unsigned int out;
  variableLength comp_Prebuf;
  ULONG compressedSize, uncompressedSize, magic;

  comp_Prebuf.size = strlen(RTF_PREBUF);
  comp_Prebuf.data = calloc(comp_Prebuf.size+1, 1);
  ALLOCCHECK_CHAR(comp_Prebuf.data);
  memcpy(comp_Prebuf.data, RTF_PREBUF, comp_Prebuf.size);

  src = p->data;
  in = 0;

  if (p->size < 20) {
    printf("File too small\n");
    return(NULL);
  }
  compressedSize = (ULONG)SwapDWord((BYTE*)src + in, 4);
  in += 4;
  uncompressedSize = (ULONG)SwapDWord((BYTE*)src + in, 4);
  in += 4;
  magic = SwapDWord((BYTE*)src + in, 4);
  in += 4;
  in += 4;


  if (compressedSize != p->size - 4) {
    printf(" Size Mismatch: %u != %i\n", compressedSize, p->size - 4);
    free(comp_Prebuf.data);
    return NULL;
  }


  if (magic == 0x414c454d) {

    dst = calloc(uncompressedSize, 1);
    ALLOCCHECK_CHAR(dst);
    memcpy(dst, src + 4, uncompressedSize);
  } else if (magic == 0x75465a4c) {

    int flagCount = 0;
    int flags = 0;

    if (comp_Prebuf.size >= INT_MAX - uncompressedSize) {
       printf("Corrupted file\n");
       exit(-1);
    }
    dst = calloc(comp_Prebuf.size + uncompressedSize, 1);
    ALLOCCHECK_CHAR(dst);
    memcpy(dst, comp_Prebuf.data, comp_Prebuf.size);
    out = comp_Prebuf.size;
    while (out < (comp_Prebuf.size + uncompressedSize)) {

      flags = (flagCount++ % 8 == 0) ? src[in++] : flags >> 1;
      if ((flags & 1) == 1) {
        unsigned int offset = src[in++];
        unsigned int length = src[in++];
        unsigned int end;
        offset = (offset << 4) | (length >> 4);
        length = (length & 0xF) + 2;


        offset = (out / 4096) * 4096 + offset;
        if (offset >= out)
          offset -= 4096;


        end = offset + length;
        while ((offset < end) && (out < (comp_Prebuf.size + uncompressedSize))
             && (offset < (comp_Prebuf.size + uncompressedSize)))
          dst[out++] = dst[offset++];
      } else {
        if ((out >= (comp_Prebuf.size + uncompressedSize)) ||
            (in >= p->size)) {
          printf("Corrupted stream\n");
          exit(-1);
        }
        dst[out++] = src[in++];
      }
    }

    src = dst;
    dst = calloc(uncompressedSize, 1);
    ALLOCCHECK_CHAR(dst);
    memcpy(dst, src + comp_Prebuf.size, uncompressedSize);
    free(src);
    *size = uncompressedSize;
    free(comp_Prebuf.data);
    return dst;
  } else {
    printf("Unknown compression type (magic number %x)\n", magic);
  }
  free(comp_Prebuf.data);
  return NULL;
}
