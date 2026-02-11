init(int inX1, int inY1, int inX2, int inY2,
						 int recWidth, int recHeight,
						 int totalRec, BrowDispFP dispFunc,
						 int dispFrame, int minInterSpace)
{
	x1 = inX1;
	y1 = inY1;
	x2 = inX2;
	y2 = inY2;

	ix1 = x1+6;
	iy1 = y1+6;
	ix2 = x2-6-SCROLL_BAR_WIDTH;
   iy2 = y2-6;


	if( recWidth <= 0 )
      rec_width = ix2-ix1+1;
   else
      rec_width = recWidth;

   rec_height = recHeight;

	disp_rec_func   = dispFunc;
	disp_frame      = dispFrame;

	x_max_rec = (ix2-ix1+minInterSpace+1) / (rec_width +minInterSpace);
	y_max_rec = (iy2-iy1+minInterSpace+1) / (rec_height+minInterSpace);

	detect_pull_flag = 1;

   err_if( x_max_rec <= 0 || y_max_rec <= 0 )
      err_now( "VBrowse::init() error : disp_max_rec <= 0" );


   if( x_max_rec > 1 )
      rec_x_space = minInterSpace + (ix2-ix1+minInterSpace+1) % (rec_width +minInterSpace)/(x_max_rec-1);
   else
      rec_x_space = minInterSpace;

   if( y_max_rec > 1 )
      rec_y_space = minInterSpace + (iy2-iy1+minInterSpace+1) % (rec_height+minInterSpace)/(y_max_rec-1);
   else
      rec_y_space = minInterSpace;

	init_var(totalRec,-1);

   init_flag = 1;


   paint();
}
