__mloop_select_item(
	MenuParameters *pmp, mloop_evh_input_t *in, mloop_evh_data_t *med,
	Bool does_submenu_overlap, Bool *pdoes_popdown_submenu_overlap)
{
	in->mif.is_item_entered_by_key_press = in->mif.is_key_press;
	med->popup_delay_10ms = 0;


	if (MR_SELECTED_ITEM(pmp->menu))
	{


		if (in->mrPopup && in->mrPopup != in->mrPopdown)
		{
			in->mrPopdown = in->mrPopup;
			med->popdown_delay_10ms = 0;
			*pdoes_popdown_submenu_overlap = does_submenu_overlap;
			in->mrPopup = NULL;
		}
		select_menu_item(
			pmp->menu, MR_SELECTED_ITEM(pmp->menu), False,
			(*pmp->pexc)->w.fw);
	}

	select_menu_item(pmp->menu, med->mi, True, (*pmp->pexc)->w.fw);

	return;
}
