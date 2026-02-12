free_fontdataOC(
    Display	*dpy,
    FontData	font_data,
    int		font_data_count)
{
    for( ; font_data_count-- ; font_data++) {
	if(font_data->xlfd_name){
	    Xfree(font_data->xlfd_name);
	    font_data->xlfd_name = NULL;
	}
	if(font_data->font){
	    if(font_data->font->fid)
		XFreeFont(dpy,font_data->font);
	    else
		XFreeFontInfo(NULL, font_data->font, 1);
	    font_data->font = NULL;
	}


    }
}
