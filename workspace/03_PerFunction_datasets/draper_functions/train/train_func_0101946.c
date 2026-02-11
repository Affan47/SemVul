XzCheck_Init(CXzCheck *p, int mode)
{
  p->mode = mode;
  switch (mode)
  {
    case XZ_CHECK_CRC32: p->crc = CRC_INIT_VAL; break;
    case XZ_CHECK_CRC64: p->crc64 = CRC64_INIT_VAL; break;
    case XZ_CHECK_SHA256:
        p->sha = cl_hash_init("sha256");
        break;
  }
}
