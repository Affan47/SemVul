static uint32_t qxl_crc32(const uint8_t *p, unsigned len)
{


    return crc32(0xffffffff, p, len) ^ 0xffffffff;
}
