disp_all()
{
	int recNo;

	if( !vga_front_only && !vga.use_back_buf )
		vga_util.blt_buf( ix1, iy1, ix2, iy2, 0 );

	int scrollRecno = (disp_frame && x_max_rec==1) ? rec_no : top_rec_no;

	scroll_bar.refresh( scrollRecno, 1, disp_max_rec,
				 (disp_frame && x_max_rec==1 ? 1 : disp_max_rec),
				 total_rec_num );

	for( recNo=top_rec_no ; recNo<=total_rec_num && recNo<top_rec_no+disp_max_rec ; recNo++ )
	{
		disp_one( recNo, DISP_REC );

		if( recNo == rec_no )
			disp_one( recNo, DISP_HIGH );
	}
}
