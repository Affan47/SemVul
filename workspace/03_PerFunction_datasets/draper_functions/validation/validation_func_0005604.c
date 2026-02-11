canvas_vbox_event (ECanvasVbox *vbox,
                   GdkEventKey *key,
                   ETable *etable)
{
	if (key->type != GDK_KEY_PRESS  &&
		key->type != GDK_KEY_RELEASE) {
		return FALSE;
	}
	switch (key->keyval) {
		case GDK_KEY_Tab:
		case GDK_KEY_KP_Tab:
		case GDK_KEY_ISO_Left_Tab:
			if ((key->state & GDK_CONTROL_MASK) && etable->click_to_add) {
				gnome_canvas_item_grab_focus (etable->click_to_add);
				break;
			}
		default:
			return FALSE;
	}

	return TRUE;
}
