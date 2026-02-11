init_line_info_color_pair(struct line_info *info, enum line_type type,
	int default_bg, int default_fg)
{
	int bg = info->bg == COLOR_DEFAULT ? default_bg : info->bg;
	int fg = info->fg == COLOR_DEFAULT ? default_fg : info->fg;

	init_pair(COLOR_ID(type), fg, bg);
}
