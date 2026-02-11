XzCheck_Final(CXzCheck *p, Byte *digest)
{
  switch (p->mode)
  {
    case XZ_CHECK_CRC32:
      SetUi32(digest, CRC_GET_DIGEST(p->crc));
      break;
    case XZ_CHECK_CRC64:
    {
      int i;
      UInt64 v = CRC64_GET_DIGEST(p->crc64);
      for (i = 0; i < 8; i++, v >>= 8)
        digest[i] = (Byte)(v & 0xFF);
      break;
    }
    case XZ_CHECK_SHA256:
      if (!(p->sha))
          return 0;

      cl_finish_hash(p->sha, digest);
      break;
    default:
      return 0;
  }
  return 1;
}
