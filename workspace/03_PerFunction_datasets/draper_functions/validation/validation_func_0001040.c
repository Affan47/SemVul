branch_get_color(enum color_branch ix)
{
	if (branch_use_color > 0)
		return branch_colors[ix];
	return "";
}
