write_tab(VMG_ int indent, int multiple)
{
    int maxcol;


    if (html_target_)
    {
        char buf[40];


        sprintf(buf, "<TAB %s=%d>",
                indent != 0 ? "INDENT" : "MULTIPLE",
                indent != 0 ? indent : multiple);


        buffer_string(vmg_ buf);
    }
    else if (multiple != 0)
    {

        maxcol = get_buffer_maxcol();


        do
        {

            if (linecol_ >= maxcol)
                break;


            linebuf_[linepos_] = ' ';
            flagbuf_[linepos_] = cur_flags_;
            colorbuf_[linepos_] = cur_color_;


            ++linepos_;


            ++linecol_;
        } while ((linecol_ + 1) % multiple != 0);
    }
    else if (indent != 0)
    {


        for (maxcol = get_buffer_maxcol() ;
             indent != 0 && linecol_ < maxcol ; --indent)
        {

            linebuf_[linepos_] = ' ';
            flagbuf_[linepos_] = cur_flags_;
            colorbuf_[linepos_] = cur_color_;


            ++linepos_;
            ++linecol_;
        }
    }
}
