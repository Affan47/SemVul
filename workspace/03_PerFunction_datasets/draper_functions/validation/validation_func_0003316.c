mainwindow_recalc_ypos(MAIN_WINDOW_REC *window, int placement)
{
	GSList *tmp;

	for (tmp = window->statusbars; tmp != NULL; tmp = tmp->next) {
		STATUSBAR_REC *bar = tmp->data;

		if (bar->config->placement == placement) {
			statusbars_recalc_ypos(bar);
                        break;
		}
	}
}
