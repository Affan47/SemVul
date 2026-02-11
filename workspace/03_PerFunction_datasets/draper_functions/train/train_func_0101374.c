ui_window_focus(UiWin *w) {
	UiCursesWin *win = (UiCursesWin*)w;
	UiCursesWin *oldsel = win->ui->selwin;
	win->ui->selwin = win;
	if (oldsel)
		ui_window_draw_status((UiWin*)oldsel);
	ui_window_draw_status(w);
}
