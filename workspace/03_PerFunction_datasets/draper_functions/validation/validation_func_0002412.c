MG_popup_if_renamed(AW_window *aww, AW_CL cl_create_window) {
    GB_ERROR error = MG_expect_renamed();
    if (!error) {
        static GB_HASHI *popup_hash = GBS_create_hashi(10);
        AW_window       *aw_popup   = (AW_window*)GBS_read_hashi(popup_hash, cl_create_window);

        if (!aw_popup) {
            typedef AW_window *(*window_creator)(AW_root *);
            window_creator create_window = (window_creator)cl_create_window;
            aw_popup                     = create_window(aww->get_root());
            GBS_write_hashi(popup_hash, cl_create_window, (long)aw_popup);
        }

        aw_popup->activate();
    }

    if (error) aw_message(error);
}
