ED4_motion_cb( AW_window *aww, AW_CL cd1, AW_CL cd2 )
{
    AWUSE(cd1);
    AWUSE(cd2);
    AW_event event;

    ED4_ROOT->use_window(aww);

    aww->get_event(&event);

    if (event.type == AW_Mouse_Drag && event.button == ED4_B_MIDDLE_BUTTON) {
        if (ED4_ROOT->scroll_picture.scroll) {
            int xdiff    = ED4_ROOT->scroll_picture.old_x - event.x;
            int ydiff    = ED4_ROOT->scroll_picture.old_y - event.y;
            int new_xpos = aww->slider_pos_horizontal + (xdiff*ED4_ROOT->aw_root->awar(ED4_AWAR_SCROLL_SPEED_X)->read_int())/10;
            int new_ypos = aww->slider_pos_vertical   + (ydiff*ED4_ROOT->aw_root->awar(ED4_AWAR_SCROLL_SPEED_Y)->read_int())/10;

            if (xdiff<0) {
                if (new_xpos<0) new_xpos = 0;
            }
            else if (xdiff>0) {
                int max_xpos = get_max_slider_xpos();
                if (max_xpos<0) max_xpos = 0;
                if (new_xpos>max_xpos) new_xpos = max_xpos;
            }

            if (ydiff<0) {
                if (new_ypos<0) new_ypos = 0;
            }
            else if (ydiff>0) {
                int max_ypos = get_max_slider_ypos();
                if (max_ypos<0) max_ypos = 0;
                if (new_ypos>max_ypos) new_ypos = max_ypos;
            }

            if (new_xpos!=aww->slider_pos_horizontal) {
                aww->set_horizontal_scrollbar_position(new_xpos);
                ED4_horizontal_change_cb(aww, cd1, cd2 );
                ED4_ROOT->scroll_picture.old_x = event.x;
            }

            if (new_ypos!=aww->slider_pos_vertical) {
                aww->set_vertical_scrollbar_position(new_ypos);
                ED4_vertical_change_cb(aww, cd1, cd2 );
                ED4_ROOT->scroll_picture.old_y = event.y;
            }
        }
    }
    else {

#if defined(DEBUG) && 0
        if (event.button==ED4_B_LEFT_BUTTON) {
            printf("[ED4_motion_cb] type=%i x=%i y=%i ", (int)event.type, (int)event.x, (int)event.y);
        }
#endif

        AW_pos win_x = event.x;
        AW_pos win_y = event.y;
        ED4_ROOT->win_to_world_coords( aww, &win_x, &win_y);
        event.x = (int) win_x;
        event.y = (int) win_y;

#if defined(DEBUG) && 0
        if (event.button==ED4_B_LEFT_BUTTON) {
            printf("-> x=%i y=%i\n", (int)event.type, (int)event.x, (int)event.y);
        }
#endif

        GB_transaction dummy(GLOBAL_gb_main);
        ED4_ROOT->main_manager->event_sent_by_parent( &event, aww );
    }
}
