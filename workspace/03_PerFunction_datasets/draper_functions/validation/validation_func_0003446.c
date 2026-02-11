__obstack_vprintf_chk (struct obstack *obstack, int flags, const char *format,
		       va_list args)
{
  struct obstack_FILE
    {
      struct _IO_obstack_file ofile;
    } new_f;
  int result;
  int size;
  int room;

#ifdef _IO_MTSAFE_IO
  new_f.ofile.file.file._lock = NULL;
#endif

  _IO_no_init (&new_f.ofile.file.file, _IO_USER_LOCK, -1, NULL, NULL);
  _IO_JUMPS (&new_f.ofile.file) = &_IO_obstack_jumps;
  room = obstack_room (obstack);
  size = obstack_object_size (obstack) + room;
  if (size == 0)
    {


      obstack_make_room (obstack, 64);


      room = obstack_room (obstack);
      size = room;

      assert (size != 0);
    }

  _IO_str_init_static_internal ((struct _IO_strfile_ *) &new_f.ofile,
				obstack_base (obstack),
				size, obstack_next_free (obstack));

  assert (size == (new_f.ofile.file.file._IO_write_end
		   - new_f.ofile.file.file._IO_write_base));
  assert (new_f.ofile.file.file._IO_write_ptr
	  == (new_f.ofile.file.file._IO_write_base
	      + obstack_object_size (obstack)));
  obstack_blank_fast (obstack, room);

  new_f.ofile.obstack = obstack;


  if (flags > 0)
    new_f.ofile.file.file._flags2 |= _IO_FLAGS2_FORTIFY;

  result = _IO_vfprintf (&new_f.ofile.file.file, format, args);


  obstack_blank_fast (obstack, (new_f.ofile.file.file._IO_write_ptr
				- new_f.ofile.file.file._IO_write_end));

  return result;
}
