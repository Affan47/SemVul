awt_create_loadsave_colored_window(AW_root *aw_root, AW_CL cl_csd) {
    static AW_window **aw_loadsave = 0;
    if (!aw_loadsave) {

        aw_root->awar_string(AWT_COLOR_LOADSAVE_NAME, "", AW_ROOT_DEFAULT);
        aw_loadsave = (AW_window**)GB_calloc(AWT_QUERY_ITEM_TYPES, sizeof(*aw_loadsave));
    }

    color_save_data     *csd  = (color_save_data*)cl_csd;
    AWT_QUERY_ITEM_TYPE  type = csd->cmd->sel->type;

    awt_assert(type<AWT_QUERY_ITEM_TYPES);

    if (!aw_loadsave[type]) {

        AW_window_simple *aws = new AW_window_simple;
        {
            char *window_id = GBS_global_string_copy("colorset_loadsave_%s", csd->items_name);
            aws->init(aw_root, window_id, GBS_global_string("Load/Save %s colorset", csd->items_name));
            free(window_id);
        }

        aws->load_xfig("color_loadsave.fig");

        aws->at("close");
        aws->callback((AW_CB0) AW_POPDOWN);
        aws->create_button("CLOSE","CLOSE", "C");

        aws->at("help");
        aws->callback(AW_POPUP_HELP,(AW_CL)"color_loadsave.hlp");
        aws->create_button("HELP","HELP","H");

        aws->at("name");
        aws->create_input_field(AWT_COLOR_LOADSAVE_NAME, 60);

        awt_assert(csd->sel_id == 0);
        aws->at("list");
        csd->sel_id = aws->create_selection_list(AWT_COLOR_LOADSAVE_NAME, 0, 0, 0, 0);
        csd->aww    = aws;

        update_colorset_selection_list(csd);

        aws->at("save");
        aws->callback(awt_loadsave_colorset, (AW_CL)csd, (AW_CL)0);
        aws->create_button("save", "Save", "S");

        aws->at("load");
        aws->callback(awt_loadsave_colorset, (AW_CL)csd, (AW_CL)1);
        aws->create_button("load", "Load", "L");

        aws->at("overlay");
        aws->callback(awt_loadsave_colorset, (AW_CL)csd, (AW_CL)2);
        aws->create_button("overlay", "Overlay", "O");

        aws->at("delete");
        aws->callback(awt_loadsave_colorset, (AW_CL)csd, (AW_CL)3);
        aws->create_button("delete", "Delete", "D");

        aws->at("reset");
        aws->callback(awt_clear_all_colors, (AW_CL)csd);
        aws->create_button("reset", "Reset", "R");


        {
            GB_transaction  ta(csd->cmd->gb_main);
            GBDATA         *gb_colorset = get_colorset_root(csd);
            GB_add_callback(gb_colorset, GB_CB_CHANGED, colorset_changed_cb, (int*)csd);
        }

        aw_loadsave[type] = aws;
    }

    return aw_loadsave[type];
}
