display_debug_aranges (struct dwarf_section *section,
		       void *file ATTRIBUTE_UNUSED)
{
  unsigned char *start = section->start;
  unsigned char *end = start + section->size;

  introduce (section, false);


  load_debug_info (file);

  while (start < end)
    {
      unsigned char *hdrptr;
      DWARF2_Internal_ARange arange;
      unsigned char *addr_ranges;
      dwarf_vma length;
      dwarf_vma address;
      dwarf_vma     sec_off;
      unsigned char address_size;
      unsigned int  offset_size;
      unsigned char *end_ranges;

      hdrptr = start;
      sec_off = hdrptr - section->start;

      SAFE_BYTE_GET_AND_INC (arange.ar_length, hdrptr, 4, end);
      if (arange.ar_length == 0xffffffff)
	{
	  SAFE_BYTE_GET_AND_INC (arange.ar_length, hdrptr, 8, end);
	  offset_size = 8;
	}
      else
	offset_size = 4;

      if (arange.ar_length > (size_t) (end - hdrptr))
	{
	  warn (_("Debug info is corrupted, %s header at %#lx has length %s\n"),
		section->name,
		(unsigned long) sec_off,
		dwarf_vmatoa ("x", arange.ar_length));
	  break;
	}
      end_ranges = hdrptr + arange.ar_length;

      SAFE_BYTE_GET_AND_INC (arange.ar_version, hdrptr, 2, end_ranges);
      SAFE_BYTE_GET_AND_INC (arange.ar_info_offset, hdrptr, offset_size,
			     end_ranges);

      if (num_debug_info_entries != DEBUG_INFO_UNAVAILABLE
	  && num_debug_info_entries > 0
	  && find_debug_info_for_offset (arange.ar_info_offset) == NULL)
	warn (_(".debug_info offset of 0x%lx in %s section does not point to a CU header.\n"),
	      (unsigned long) arange.ar_info_offset, section->name);

      SAFE_BYTE_GET_AND_INC (arange.ar_pointer_size, hdrptr, 1, end_ranges);
      SAFE_BYTE_GET_AND_INC (arange.ar_segment_size, hdrptr, 1, end_ranges);

      if (arange.ar_version != 2 && arange.ar_version != 3)
	{


	  if (arange.ar_version)
	    warn (_("Only DWARF 2 and 3 aranges are currently supported.\n"));
	  break;
	}

      printf (_("  Length:                   %ld\n"),
	      (long) arange.ar_length);
      printf (_("  Version:                  %d\n"), arange.ar_version);
      printf (_("  Offset into .debug_info:  0x%lx\n"),
	      (unsigned long) arange.ar_info_offset);
      printf (_("  Pointer Size:             %d\n"), arange.ar_pointer_size);
      printf (_("  Segment Size:             %d\n"), arange.ar_segment_size);

      address_size = arange.ar_pointer_size + arange.ar_segment_size;


      if (address_size == 0 || address_size > 8)
	{
	  error (_("Invalid address size in %s section!\n"),
		 section->name);
	  break;
	}


      if ((address_size & (address_size - 1)) != 0)
	{
	  warn (_("Pointer size + Segment size is not a power of two.\n"));
	  break;
	}

      if (address_size > 4)
	printf (_("\n    Address            Length\n"));
      else
	printf (_("\n    Address    Length\n"));

      addr_ranges = hdrptr;


      addr_ranges += (2 * address_size - 1
		      - (hdrptr - start - 1) % (2 * address_size));

      while (2 * address_size <= end_ranges - addr_ranges)
	{
	  SAFE_BYTE_GET_AND_INC (address, addr_ranges, address_size,
				 end_ranges);
	  SAFE_BYTE_GET_AND_INC (length, addr_ranges, address_size,
				 end_ranges);
	  printf ("    ");
	  print_dwarf_vma (address, address_size);
	  print_dwarf_vma (length, address_size);
	  putchar ('\n');
	}

      start = end_ranges;
    }

  printf ("\n");

  return 1;
}
