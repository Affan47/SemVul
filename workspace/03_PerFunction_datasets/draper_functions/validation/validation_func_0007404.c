emit_change (GOComboPixmaps *combo)
{
	if (_go_combo_is_updating (GO_COMBO_BOX (combo)))
		return;
	g_signal_emit (combo, go_combo_pixmaps_signals[CHANGED], 0,
		g_array_index (combo->elements, Element, combo->selected_index).id);
	go_combo_box_popup_hide (GO_COMBO_BOX (combo));
}
