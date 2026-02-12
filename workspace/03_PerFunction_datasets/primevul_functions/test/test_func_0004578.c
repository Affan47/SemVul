load_build_id_debug_file (const char * main_filename ATTRIBUTE_UNUSED, void * main_file)
{
  if (! load_debug_section (note_gnu_build_id, main_file))
    return;

  struct dwarf_section * section = & debug_displays [note_gnu_build_id].section;
  if (section == NULL)
    {
      warn (_("Unable to load the .note.gnu.build-id section\n"));
      return;
    }

  if (section->start == NULL || section->size < 0x18)
    {
      warn (_(".note.gnu.build-id section is corrupt/empty\n"));
      return;
    }


  unsigned long build_id_size;
  build_id_size = byte_get (section->start + 4, 4);
  if (build_id_size < 8)
    {
      warn (_(".note.gnu.build-id data size is too small\n"));
      return;
    }

  if (build_id_size > (section->size - 16))
    {
      warn (_(".note.gnu.build-id data size is too bug\n"));
      return;
    }

  char * filename;
  filename = xmalloc (strlen (".build-id/")
		      + build_id_size * 2 + 2
		      + strlen (".debug")


		      + strlen ("/usrlib64/debug/usr")
		      + 1);
  void * handle;

  static const char * prefixes[] =
    {
      "",
      ".debug/",
      "/usr/lib/debug/",
      "/usr/lib/debug/usr/",
      "/usr/lib64/debug/",
      "/usr/lib64/debug/usr"
    };
  long unsigned int i;

  for (i = 0; i < ARRAY_SIZE (prefixes); i++)
    {
      handle = try_build_id_prefix (prefixes[i], filename,
				    section->start + 16, build_id_size);
      if (handle != NULL)
	break;
    }

  if (handle == NULL)
    {


      free (filename);
      return;
    }

  add_separate_debug_file (filename, handle);
}
