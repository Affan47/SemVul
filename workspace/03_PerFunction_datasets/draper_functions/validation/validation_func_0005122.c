get_page( debugger_breakpoint_type type, libspectrum_word address )
{
  memory_page *bank;

  switch( type ) {
  case DEBUGGER_BREAKPOINT_TYPE_EXECUTE:
  case DEBUGGER_BREAKPOINT_TYPE_READ:
    bank = memory_map_read;
    break;

  case DEBUGGER_BREAKPOINT_TYPE_WRITE:
    bank = memory_map_write;
    break;

  default:
    ui_error( UI_ERROR_ERROR,
	      "%s:get_page: unexpected breakpoint type %d", __FILE__, type );
    fuse_abort();
  }

  return &bank[ address >> MEMORY_PAGE_SIZE_LOGARITHM ];
}
