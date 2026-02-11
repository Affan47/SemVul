itemChange( GraphicsItemChange change, const QVariant &value )
{
    QVariant ret = QGraphicsWidget::itemChange( change, value );

    if( change == ItemPositionHasChanged )
        emit geometryChanged();
    return ret;
}
