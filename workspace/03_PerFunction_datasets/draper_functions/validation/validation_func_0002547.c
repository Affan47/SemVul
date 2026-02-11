dialog_consolidate (WBCGtk *wbcg)
{
	ConsolidateState *state;
	SheetView *sv;
	Sheet *sheet;

	g_return_if_fail (wbcg != NULL);
	sv = wb_control_cur_sheet_view (WORKBOOK_CONTROL (wbcg));
	sheet = sv_sheet (sv);


	if (gnumeric_dialog_raise_if_exists (wbcg, CONSOLIDATE_KEY)) {
		return;
	}


	state = g_new0 (ConsolidateState, 1);

	if (dialog_tool_init ((GenericToolState *)state, wbcg, sheet,
			      GNUMERIC_HELP_LINK_CONSOLIDATE,
			      "consolidate.ui", "Consolidate",
			      _("Could not create the Consolidate dialog."),
			      CONSOLIDATE_KEY,
			      G_CALLBACK (cb_consolidate_ok_clicked),
			      NULL,
			      G_CALLBACK (dialog_set_button_sensitivity),
			      0))
		return;

	gnm_dao_set_put (GNM_DAO (state->base.gdao), TRUE, TRUE);
	dialog_consolidate_tool_init (state);
	gtk_widget_show (GTK_WIDGET (state->base.dialog));
}
