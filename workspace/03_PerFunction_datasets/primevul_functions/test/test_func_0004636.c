display_debug_links (struct dwarf_section *  section,
		     void *                  file ATTRIBUTE_UNUSED)
{
  const unsigned char * filename;
  unsigned int          filelen;

  introduce (section, false);


  filename =  section->start;
  filelen = strnlen ((const char *) filename, section->size);
  if (filelen == section->size)
    {
      warn (_("The debuglink filename is corrupt/missing\n"));
      return 0;
    }

  printf (_("  Separate debug info file: %s\n"), filename);

  if (startswith (section->name, ".gnu_debuglink"))
    {
      unsigned int          crc32;
      unsigned int          crc_offset;

      crc_offset = filelen + 1;
      crc_offset = (crc_offset + 3) & ~3;
      if (crc_offset + 4 > section->size)
	{
	  warn (_("CRC offset missing/truncated\n"));
	  return 0;
	}

      crc32 = byte_get (filename + crc_offset, 4);

      printf (_("  CRC value: %#x\n"), crc32);

      if (crc_offset + 4 < section->size)
	{
	  warn (_("There are %#lx extraneous bytes at the end of the section\n"),
		(long)(section->size - (crc_offset + 4)));
	  return 0;
	}
    }
  else
    {
      const unsigned char * build_id = section->start + filelen + 1;
      bfd_size_type         build_id_len = section->size - (filelen + 1);
      bfd_size_type         printed;


      if (build_id_len < 0x14)
	{
	  warn (_("Build-ID is too short (%#lx bytes)\n"), (long) build_id_len);
	  return 0;
	}

      printed = printf (_("  Build-ID (%#lx bytes):"), (long) build_id_len);
      display_data (printed, build_id, build_id_len);
      putchar ('\n');
    }

  putchar ('\n');
  return 1;
}
