gnc_entry_ledger_config_action (GncEntryLedger *ledger)
{
    ComboCell *cell;

    cell = (ComboCell *) gnc_table_layout_get_cell (ledger->table->layout,
            ENTRY_ACTN_CELL);
    if (!cell) return;


    gnc_combo_cell_add_menu_item (cell, _("Hours"));
    gnc_combo_cell_add_menu_item (cell, _("Project"));
    gnc_combo_cell_add_menu_item (cell, _("Material"));
}
