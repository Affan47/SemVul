slotSetFilter()
{
    m_filter = m_searchEdit->text();

    m_coverView->clearSelection();
    uint i = 0;
    QListWidgetItem *item = m_coverView->item( i );
    while ( item )
    {
        QListWidgetItem *tmp = m_coverView->item( i + 1 );
        m_coverView->takeItem( i );
        item = tmp;
    }

    foreach( QListWidgetItem *item, m_coverItems )
    {
        CoverViewItem *coverItem = static_cast<CoverViewItem*>(item);
        if( coverItem->album().contains( m_filter, Qt::CaseInsensitive ) || coverItem->artist().contains( m_filter, Qt::CaseInsensitive ) )
            m_coverView->insertItem( m_coverView->count() -  1, item );
    }


    changeView( m_currentView, true );
    updateStatusBar();
}
