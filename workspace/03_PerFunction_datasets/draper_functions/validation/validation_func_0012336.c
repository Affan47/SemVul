lto_input_location (struct lto_input_block *ib, struct data_in *data_in)
{
  expanded_location xloc;

  xloc.file = input_string (data_in, ib);
  if (xloc.file == NULL)
    return UNKNOWN_LOCATION;

  xloc.file = canon_file_name (xloc.file);
  xloc.line = lto_input_sleb128 (ib);
  xloc.column = lto_input_sleb128 (ib);
  xloc.sysp = lto_input_sleb128 (ib);

  if (data_in->current_file != xloc.file)
    {
      if (data_in->current_file)
	linemap_add (line_table, LC_LEAVE, false, NULL, 0);

      linemap_add (line_table, LC_ENTER, xloc.sysp, xloc.file, xloc.line);
    }
  else if (data_in->current_line != xloc.line)
    linemap_line_start (line_table, xloc.line, xloc.column);

  data_in->current_file = xloc.file;
  data_in->current_line = xloc.line;
  data_in->current_col = xloc.column;

  return linemap_position_for_column (line_table, xloc.column);
}
