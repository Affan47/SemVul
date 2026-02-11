mouseEventInHeader( const QMouseEvent* event ) const
{
    QModelIndex index = indexAt( event->pos() );
    if ( index.data( GroupRole ).toInt() == Grouping::Head )
    {
        QPoint mousePressPos = event->pos();
        mousePressPos.rx() += horizontalOffset();
        mousePressPos.ry() += verticalOffset();
        return m_prettyDelegate->insideItemHeader( mousePressPos, rectForIndex( index ) );
    }
    return false;
}
