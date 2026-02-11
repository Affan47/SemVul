cb_select_lineend(GtkOptionMenu *option_menu, FileInfo *selected_fi)
{
	switch (gtk_option_menu_get_history(option_menu)) {
	case 1:
		selected_fi->lineend = CR+LF;
		break;
	case 2:
		selected_fi->lineend = CR;
		break;
	default:
		selected_fi->lineend = LF;
	}
}
