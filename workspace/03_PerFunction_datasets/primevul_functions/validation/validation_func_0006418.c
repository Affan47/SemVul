show_pum(int prev_w_wrow, int prev_w_leftcol)
{

    int n = RedrawingDisabled;

    RedrawingDisabled = 0;


    setcursor();
    if (prev_w_wrow != curwin->w_wrow || prev_w_leftcol != curwin->w_leftcol)
	ins_compl_del_pum();

    ins_compl_show_pum();
    setcursor();
    RedrawingDisabled = n;
}
