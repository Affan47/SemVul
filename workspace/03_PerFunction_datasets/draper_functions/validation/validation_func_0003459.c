update_cursor ()
{

    bool b = false;


    cursor_cur_blink_ = cursor_blink_cycle;


    while (!b && my_cursor_.line < my_vect_.size () )
    {
        if (my_cursor_.idx >= my_vect_[my_cursor_.line].idx_beg &&
            my_cursor_.idx <= my_vect_[my_cursor_.line].idx_end ) b = true;
        else if (my_cursor_.idx >  my_vect_[my_cursor_.line].idx_end)
        {
            if (my_cursor_.line ==  my_vect_.size () - 1) b = true;
            else my_cursor_.line++;
        }
        else if (my_cursor_.idx <  my_vect_[my_cursor_.line].idx_beg)
        {
            my_cursor_.line--;
        }
    }


    my_cursor_.pos_x = 0;

    u_int16 j = my_vect_[my_cursor_.line].idx_beg;
    while (j < my_cursor_.idx) {
        my_cursor_.pos_x+= (*my_font_) [ucd (j)].length ();
        j++;
    }

    my_cursor_.pos_y = (my_cursor_.line - start_line_) * my_font_->height ();

    if (my_cursor_.pos_y > height ())
    {


    }
}
