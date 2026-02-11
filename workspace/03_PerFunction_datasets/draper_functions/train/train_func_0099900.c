display_loc_list_dwo (struct dwarf_section *section,
                      unsigned char **start_ptr,
                      int debug_info_entry,
                      unsigned long offset,
                      int has_frame_base)
{
  unsigned char *start = *start_ptr;
  unsigned char *section_end = section->start + section->size;
  unsigned long cu_offset = debug_information [debug_info_entry].cu_offset;
  unsigned int pointer_size = debug_information [debug_info_entry].pointer_size;
  unsigned int offset_size = debug_information [debug_info_entry].offset_size;
  int dwarf_version = debug_information [debug_info_entry].dwarf_version;
  int entry_type;
  unsigned short length;
  int need_frame_base;
  dwarf_vma idx;
  unsigned int bytes_read;

  while (1)
    {
      printf ("    %8.8lx ", offset);

      if (start + 2 > section_end)
        {
          warn (_("Location list starting at offset 0x%lx is not terminated.\n"),
                offset);
          break;
        }

      entry_type = byte_get (start, 1);
      start++;
      switch (entry_type)
        {
          case 0:
            idx = byte_get (start, 1);
            start++;
            *start_ptr = start;
            if (idx == 0)
              printf (_("<End of list>\n"));
            else
              warn (_("Location list starting at offset 0x%lx is not terminated.\n"),
                    offset);
            return;
          case 1:
            idx = read_leb128 (start, &bytes_read, 0);
            start += bytes_read;
            print_dwarf_vma (idx, pointer_size);
            printf (_("(base address index)\n"));
            continue;
          case 2:
            idx = read_leb128 (start, &bytes_read, 0);
            start += bytes_read;
            print_dwarf_vma (idx, pointer_size);
            idx = read_leb128 (start, &bytes_read, 0);
            start += bytes_read;
            print_dwarf_vma (idx, pointer_size);
            break;
          default:
            warn (_("Unknown location-list type 0x%x.\n"), entry_type);
            *start_ptr = start;
            return;
        }

      if (start + 2 > section_end)
        {
          warn (_("Location list starting at offset 0x%lx is not terminated.\n"),
                offset);
          break;
        }

      length = byte_get (start, 2);
      start += 2;

      if (start + length > section_end)
        {
          warn (_("Location list starting at offset 0x%lx is not terminated.\n"),
                offset);
          break;
        }

      putchar ('(');
      need_frame_base = decode_location_expression (start,
                                                    pointer_size,
                                                    offset_size,
                                                    dwarf_version,
                                                    length,
                                                    cu_offset, section);
      putchar (')');

      if (need_frame_base && !has_frame_base)
        printf (_(" [without DW_AT_frame_base]"));

      putchar ('\n');

      start += length;
    }

  *start_ptr = start;
}
