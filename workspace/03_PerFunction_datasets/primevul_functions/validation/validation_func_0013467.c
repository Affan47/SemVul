static int __init no_scroll(char *str)
{


	vga_hardscroll_user_enable = vga_hardscroll_enabled = false;
	return 1;
}
