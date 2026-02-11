iemgui_modulo_color(int col)
{
    while(col >= IEM_GUI_MAX_COLOR)
        col -= IEM_GUI_MAX_COLOR;
    while(col < 0)
        col += IEM_GUI_MAX_COLOR;
    return(col);
}
