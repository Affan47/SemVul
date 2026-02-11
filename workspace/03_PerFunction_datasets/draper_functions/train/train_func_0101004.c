notifyItemsRemoved( const QSet<quint64> &removedItems )
{
    DEBUG_BLOCK

    foreach( quint64 removedItem, removedItems )
    {
        AlbumId album = albumForItem( removedItem );


        if ( removedItem == currentItem() )
        {
            planOne();
            if ( !m_plannedItems.isEmpty() )
                setCurrentItem( m_plannedItems.first() );
        }

        m_plannedItems.removeAll( removedItem );


        ItemList itemsInAlbum = m_itemsPerAlbum.value( album );
        itemsInAlbum.removeAll( removedItem );
        if ( itemsInAlbum.isEmpty() )
        {
            m_itemsPerAlbum.remove( album );
            m_plannedAlbums.removeAll( album );
        }
        else
            m_itemsPerAlbum.insert( album, itemsInAlbum );


        m_albumForItem.remove( removedItem );
    }
}
