DrawGridCells( wxDC& dc, const wxSheetSelection& blockSel )
{
    if ( !GetNumberRows() || !GetNumberCols() || GetBatchCount() )
        return;


    wxSheetSelection removedSel;
    wxSheetCoords coords;
    wxSheetCoords lastCoords(-1,-1);
    wxSheetBlock  cellBlock;
    wxPairArrayIntInt leftCols;


    wxSheetSelectionIterator revIter(blockSel, wxSSI_REVERSE);
    while (revIter.GetNext(coords) != wxSHEET_SELECTIONITER_GET_END)
    {

        if (removedSel.Contains(coords))
        {
            lastCoords = coords;
            continue;
        }


        cellBlock = GetCellBlock(coords);
        if (!cellBlock.IsOneCell())
        {

            coords = cellBlock.GetLeftTop();

            removedSel.SelectBlock(cellBlock, false);
        }


        if ((lastCoords.m_row > coords.m_row) && !HasCellValue(lastCoords))
        {
            int overflow_col = FindOverflowCell(lastCoords, dc);
            if ((overflow_col >= 0) && !blockSel.Contains(lastCoords.m_row, overflow_col))
                leftCols.SetValue(lastCoords.m_row, overflow_col);
        }


        DrawCell( dc, coords );
        lastCoords = coords;
    }


    if (ContainsGridCell(lastCoords) && !HasCellValue(lastCoords))
    {
        int overflow_col = FindOverflowCell(lastCoords, dc);
        if ((overflow_col >= 0) && !blockSel.Contains(lastCoords.m_row, overflow_col))
            leftCols.SetValue(lastCoords.m_row, overflow_col);
    }


    int n, count = leftCols.GetCount();
    for (n = 0; n < count; n++)
    {
        coords.Set(leftCols.GetItemKey(n), leftCols.GetItemValue(n));
        DrawCell( dc, coords );

    }
}
