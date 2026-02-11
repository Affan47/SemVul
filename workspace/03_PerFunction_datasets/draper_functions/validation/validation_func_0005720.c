alac_set_info(alac_file *alac, char *inputbuffer)
{
  char *ptr = inputbuffer;
  ptr += 4;
  ptr += 4;
  ptr += 4;
  ptr += 4;
  ptr += 4;

  ptr += 4;

  alac->setinfo_max_samples_per_frame = *(uint32_t*)ptr;
  if (!host_bigendian)
      _Swap32(alac->setinfo_max_samples_per_frame);
  ptr += 4;
  alac->setinfo_7a = *(uint8_t*)ptr;
  ptr += 1;
  alac->setinfo_sample_size = *(uint8_t*)ptr;
  ptr += 1;
  alac->setinfo_rice_historymult = *(uint8_t*)ptr;
  ptr += 1;
  alac->setinfo_rice_initialhistory = *(uint8_t*)ptr;
  ptr += 1;
  alac->setinfo_rice_kmodifier = *(uint8_t*)ptr;
  ptr += 1;
  alac->setinfo_7f = *(uint8_t*)ptr;
  ptr += 1;
  alac->setinfo_80 = *(uint16_t*)ptr;
  if (!host_bigendian)
      _Swap16(alac->setinfo_80);
  ptr += 2;
  alac->setinfo_82 = *(uint32_t*)ptr;
  if (!host_bigendian)
      _Swap32(alac->setinfo_82);
  ptr += 4;
  alac->setinfo_86 = *(uint32_t*)ptr;
  if (!host_bigendian)
      _Swap32(alac->setinfo_86);
  ptr += 4;
  alac->setinfo_8a_rate = *(uint32_t*)ptr;
  if (!host_bigendian)
      _Swap32(alac->setinfo_8a_rate);
  ptr += 4;

  allocate_buffers(alac);

}
