fs_nvram_offset_of(fs_nvram_t *fs, m_uint32_t address)
{
   if ((fs->flags & FS_NVRAM_FLAG_ADDR_ABSOLUTE))
      return(address - fs->addr);
   else
      return(address + 8);
}
