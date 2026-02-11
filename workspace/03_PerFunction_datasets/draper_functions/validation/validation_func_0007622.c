border_change_write( int y, int start, int end, int colour )
{
  if(   y <  DISPLAY_BORDER_HEIGHT                    ||
      ( y >= DISPLAY_BORDER_HEIGHT + DISPLAY_HEIGHT )    ) {


    set_border( y, start, end, colour );

    return;
  }


  if( start < DISPLAY_BORDER_WIDTH_COLS ) {

    int left_end =
      end > DISPLAY_BORDER_WIDTH_COLS ? DISPLAY_BORDER_WIDTH_COLS : end;

    set_border( y, start, left_end, colour );
  }


  if( end > DISPLAY_BORDER_WIDTH_COLS + DISPLAY_WIDTH_COLS ) {

    if( start < DISPLAY_BORDER_WIDTH_COLS + DISPLAY_WIDTH_COLS )
      start = DISPLAY_BORDER_WIDTH_COLS + DISPLAY_WIDTH_COLS;

    set_border( y, start, end, colour );
  }
}
