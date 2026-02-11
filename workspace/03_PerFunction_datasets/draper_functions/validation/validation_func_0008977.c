_IO_init_marker (marker, fp)
     struct _IO_marker *marker;
     _IO_FILE *fp;
{
  marker->_sbuf = fp;
  if (_IO_in_put_mode (fp))
    _IO_switch_to_get_mode (fp);
  if (_IO_in_backup (fp))
    marker->_pos = fp->_IO_read_ptr - fp->_IO_read_end;
  else
    marker->_pos = fp->_IO_read_ptr - fp->_IO_read_base;


  marker->_next = fp->_markers;
  fp->_markers = marker;
}
