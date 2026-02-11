widget_debugger_draw( void *data )
{
  static const char state[][8] = {
    "Running", "Halted", "Stepped", "Breakpt"
  };
  int x;
  char pbuf[8];

  widget_rectangle( LC(0), LR(0), 40 * 8, 11 * 8 + 4, 1 );
  widget_rectangle( LC(0), LR(11) + 2, 320, 1, 7 );

  switch ( display ) {
  case DB_REGISTERS: display_registers(); break;
  case DB_BYTES:     display_bytes();	  break;
  case DB_TEXT:      display_text();	  break;
  case DB_DISASM:    display_disasm();	  break;
  case DB_BREAKPT:   display_breakpts();  break;
  }

  widget_printstring( LC(0), LR(9) - 4, 6, state[debugger_mode] );
  widget_printstring( LC(10), LR(9) - 4, 6,
		      "\022S\021ingle step  \022C\021ontinue  Co\022m\021mand" );

  x = LC(-1);
  if( display != DB_REGISTERS )
    x = widget_printstring( x + 8, LR(10), 7, "\022R\021egs" );
  if( display != DB_BYTES )
    x = widget_printstring( x + 8, LR(10), 7, "\022B\021ytes" );
  if( display != DB_TEXT )
    x = widget_printstring( x + 8, LR(10), 7, "\022T\021ext" );
  if( display != DB_DISASM )
    x = widget_printstring( x + 8, LR(10), 7, "\022D\021isasm" );
  if( display != DB_BREAKPT )
    x = widget_printstring( x + 8, LR(10), 7, "Brea\022k\021pts" );

  widget_printstring_right( LC(25) + 4, LR(10), 5, "PC" );
  sprintf( pbuf, "%04X", PC );
  widget_printstring_fixed( LC(26) / 8, LR(10) / 8, 7, pbuf );

  widget_printstring_right( LR(35) + 4, LR(10), 5, "Bas\022e\021" );
  sprintf( pbuf, "%d", debugger_output_base );
  widget_printstring( LR(36), LR(10), 7, pbuf );

  widget_display_lines( LR(0) / 8, 12 );

  return 0;
}
