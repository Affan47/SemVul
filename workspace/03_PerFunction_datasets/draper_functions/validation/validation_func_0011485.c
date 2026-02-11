gui_gtk_mouse_deselect(GuiGtkMouse *mouse)
{
	if (! mouse->active) {
		mouse->active = 1;

		gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(mouse), 0);

		mouse->active = 0;
	}
}
