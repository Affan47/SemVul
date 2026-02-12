NCURSES_SP_NAME(_nc_mvcur_init) (NCURSES_SP_DCL0)

{
    if (SP_PARM->_ofp && NC_ISATTY(fileno(SP_PARM->_ofp))) {
	SP_PARM->_char_padding = ((BAUDBYTE * 1000 * 10)
				  / (BAUDRATE(SP_PARM) > 0
				     ? BAUDRATE(SP_PARM)
				     : 9600));
    } else {
	SP_PARM->_char_padding = 1;
    }
    if (SP_PARM->_char_padding <= 0)
	SP_PARM->_char_padding = 1;
    TR(TRACE_CHARPUT | TRACE_MOVE, ("char_padding %d msecs", SP_PARM->_char_padding));


    SP_PARM->_cr_cost = CostOf(carriage_return, 0);
    SP_PARM->_home_cost = CostOf(cursor_home, 0);
    SP_PARM->_ll_cost = CostOf(cursor_to_ll, 0);
#if USE_HARD_TABS
    if (getenv("NCURSES_NO_HARD_TABS") == 0
	&& dest_tabs_magic_smso == 0
	&& HasHardTabs()) {
	SP_PARM->_ht_cost = CostOf(tab, 0);
	SP_PARM->_cbt_cost = CostOf(back_tab, 0);
    } else {
	SP_PARM->_ht_cost = INFINITY;
	SP_PARM->_cbt_cost = INFINITY;
    }
#endif
    SP_PARM->_cub1_cost = CostOf(cursor_left, 0);
    SP_PARM->_cuf1_cost = CostOf(cursor_right, 0);
    SP_PARM->_cud1_cost = CostOf(cursor_down, 0);
    SP_PARM->_cuu1_cost = CostOf(cursor_up, 0);

    SP_PARM->_smir_cost = CostOf(enter_insert_mode, 0);
    SP_PARM->_rmir_cost = CostOf(exit_insert_mode, 0);
    SP_PARM->_ip_cost = 0;
    if (insert_padding) {
	SP_PARM->_ip_cost = CostOf(insert_padding, 0);
    }


    SP_PARM->_address_cursor = cursor_address ? cursor_address : cursor_mem_address;


    SP_PARM->_cup_cost = CostOf(TIPARM_2(SP_PARM->_address_cursor, 23, 23), 1);
    SP_PARM->_cub_cost = CostOf(TIPARM_1(parm_left_cursor, 23), 1);
    SP_PARM->_cuf_cost = CostOf(TIPARM_1(parm_right_cursor, 23), 1);
    SP_PARM->_cud_cost = CostOf(TIPARM_1(parm_down_cursor, 23), 1);
    SP_PARM->_cuu_cost = CostOf(TIPARM_1(parm_up_cursor, 23), 1);
    SP_PARM->_hpa_cost = CostOf(TIPARM_1(column_address, 23), 1);
    SP_PARM->_vpa_cost = CostOf(TIPARM_1(row_address, 23), 1);


    SP_PARM->_ed_cost = NormalizedCost(clr_eos, 1);
    SP_PARM->_el_cost = NormalizedCost(clr_eol, 1);
    SP_PARM->_el1_cost = NormalizedCost(clr_bol, 1);
    SP_PARM->_dch1_cost = NormalizedCost(delete_character, 1);
    SP_PARM->_ich1_cost = NormalizedCost(insert_character, 1);


    if (back_color_erase)
	SP_PARM->_el_cost = 0;


    SP_PARM->_dch_cost = NormalizedCost(TIPARM_1(parm_dch, 23), 1);
    SP_PARM->_ich_cost = NormalizedCost(TIPARM_1(parm_ich, 23), 1);
    SP_PARM->_ech_cost = NormalizedCost(TIPARM_1(erase_chars, 23), 1);
    SP_PARM->_rep_cost = NormalizedCost(TIPARM_2(repeat_char, ' ', 23), 1);

    SP_PARM->_cup_ch_cost = NormalizedCost(TIPARM_2(SP_PARM->_address_cursor,
						    23, 23),
					   1);
    SP_PARM->_hpa_ch_cost = NormalizedCost(TIPARM_1(column_address, 23), 1);
    SP_PARM->_cuf_ch_cost = NormalizedCost(TIPARM_1(parm_right_cursor, 23), 1);
    SP_PARM->_inline_cost = min(SP_PARM->_cup_ch_cost,
				min(SP_PARM->_hpa_ch_cost,
				    SP_PARM->_cuf_ch_cost));


    if (save_cursor != 0
	&& enter_ca_mode != 0
	&& strstr(enter_ca_mode, save_cursor) != 0) {
	T(("...suppressed sc/rc capability due to conflict with smcup/rmcup"));
	save_cursor = 0;
	restore_cursor = 0;
    }


    NCURSES_SP_NAME(_nc_mvcur_resume) (NCURSES_SP_ARG);
}
