disp_mine_info(int dispY1, int refreshFlag)
{


	if( refreshFlag == INFO_REPAINT )
		vga_util.d3_panel_up( INFO_X1, dispY1, INFO_X2, dispY1+70);


	if( !raw_id )
	{
		font_san.center_put( INFO_X1, dispY1, INFO_X2, dispY1+70, "No Natural Resources" );
		return;
	}


	int x=INFO_X1+4, y=dispY1+4;

	raw_res.put_small_raw_icon( x+1, y+1, raw_id );

	String str;

	str  = translate.process("Mining ");
	str += raw_res[raw_id]->name;

	font_san.disp( x+20, y, str, INFO_X2-2);
	y+=16;

	font_san.field( x, y, "Monthly Production", x+126, (int) production_30days(), 1, INFO_X2-2, refreshFlag, "MN_PROD");
	y+=16;

	str  = (int) stock_qty;
	str += " / ";
	str += (int) max_stock_qty;

	font_san.field( x, y, "Mined Stock", x+126, str, INFO_X2-2, refreshFlag, "MN_STOCK");
	y+=16;

	font_san.field( x, y, "Untapped Reserve", x+126, (int) reserve_qty, 1, INFO_X2-2, refreshFlag, "MN_UNTAP");
}
