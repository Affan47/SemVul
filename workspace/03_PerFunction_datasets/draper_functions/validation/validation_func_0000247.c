DrawItems( const wxPGProperty* p1, const wxPGProperty* p2 )
{
    if ( m_frozen )
        return;

    if ( m_pState->m_itemsAdded )
        PrepareAfterItemsAdded();

    wxRect rect = GetPropertyRect(p1, p2);
    if ( rect.width <= 0 )
        return;


    wxRegion region(rect);
    if ( m_wndEditor )
        region.Subtract(m_wndEditor->GetRect());
    if ( m_wndEditor2 )
        region.Subtract(m_wndEditor2->GetRect());
    if ( m_labelEditor )
        region.Subtract(m_labelEditor->GetRect());

    wxRegionIterator rects(region);

    while ( rects )
    {
        m_canvas->RefreshRect(rects.GetRect(), false);
        rects++;
    }
}
