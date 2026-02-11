XbaeMatrixFirstSelectedCell(w, row, column)
Widget w;
int *row;
int *column;
{
    int i, j;
    XbaeMatrixWidget mw;

    if (!XtIsSubclass(w, xbaeMatrixWidgetClass))
    {
        *row = *column = -1;
        return;
    }

    mw = (XbaeMatrixWidget) w;

    if (!mw->matrix.selected_cells)
    {
        *row = -1;
        *column = -1;
        return;
    }

    for (i = 0; i < mw->matrix.rows; i++)
        for (j = 0; j < mw->matrix.columns; j++)
            if (mw->matrix.selected_cells[ i ][ j ])
            {
                *row = i;
                *column = j;
                return;
            }
    *row = *column = -1;
}
