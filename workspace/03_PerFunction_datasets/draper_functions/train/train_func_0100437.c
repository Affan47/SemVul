sizeHint( const QStyleOptionViewItem &option,
                              const QModelIndex &index ) const
{


    updateFonts( option );
    QStyle *style = m_view->style();

    PixelSizes s( style );
    int viewportWidth = m_view->viewport()->width();
    int normalHeight = s.frameVMargin + qMax( s.smallIconSize, m_normalFm->height() ) + s.frameVMargin;

    const bool hasCover = index.data( PrettyTreeRoles::HasCoverRole ).toBool();


    if( hasCover )
        return QSize( viewportWidth, qMax( normalHeight, s.largeIconSize + s.frameVMargin * 2 ) );


    if( index.parent().isValid() )
        return QSize( viewportWidth, normalHeight );


    const bool hasCapacity = index.data( PrettyTreeRoles::HasCapacityRole ).toBool();

    QSize iconSize( s.largeIconSize, s.largeIconSize );
    QSize expanderSize( s.expanderIconSize, s.expanderIconSize );
    QSize titleSize( m_bigFm->boundingRect( index.data( Qt::DisplayRole ).toString() ).size() );
    QSize byLineSize( m_smallFm->boundingRect( index.data( PrettyTreeRoles::ByLineRole ).toString() ).size() );
    QSize capacitySize( hasCapacity ? 10 : 0, hasCapacity ? CAPACITYRECT_MIN_HEIGHT : 0 );

    int layoutWidth = s.frameHMargin +
        iconSize.width() + s.iconSpacing +
        qMax( titleSize.width(), byLineSize.width() ) + expanderSize.width() +
        s.frameHMargin;

    layoutWidth = qMax( viewportWidth, layoutWidth );

    int layoutHeight = s.frameVMargin + s.frameExtraMargin +
        qMax( titleSize.height(), s.smallIconSize ) + s.verticalSpace +
        qMax( capacitySize.height(), byLineSize.height() ) +
        s.frameExtraMargin + s.frameVMargin;

    return QSize( layoutWidth, layoutHeight );
}
