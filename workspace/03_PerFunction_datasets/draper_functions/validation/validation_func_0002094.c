popup_check_buttons(popup_info *pi)
{
	int			i;
	UI_BUTTON	*b;

	for ( i = 0; i < pi->nchoices; i++ ) {
		b = &Popup_button_regions[i];
		if ( b->pressed() ) {
			return i;
		}

		b = &Popup_buttons[i];
		if ( b->pressed() ) {
			return i;
		}
	}

	return POPUP_NOCHANGE;
}
