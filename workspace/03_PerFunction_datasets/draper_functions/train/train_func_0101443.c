detect_scroll()
{
   if( mouse_cursor.frame_flag )
      return 0;

   if( next_scroll_time && misc.get_time() < next_scroll_time )
      return 0;

   int rc=0;


   if( mouse.cur_x == mouse.bound_x1 )
   {
      zoom_matrix->scroll(-1,0);
      rc = 1;
   }


   if( mouse.cur_x == mouse.bound_x2 )
   {
      zoom_matrix->scroll(1,0);
      rc = 1;
   }


   if( mouse.cur_y == mouse.bound_y1 )
   {
      zoom_matrix->scroll(0,-1);
      rc = 1;
   }


   if( mouse.cur_y == mouse.bound_y2 )
   {
      zoom_matrix->scroll(0,1);
      rc = 1;
   }


   if( rc )
   {
      sys.zoom_need_redraw = 1;
      next_scroll_time     = misc.get_time() + 500/(config.scroll_speed+1);
   }

   return rc;
}
