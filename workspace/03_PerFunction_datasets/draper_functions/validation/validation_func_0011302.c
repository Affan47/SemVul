moveFocusRight()
{
    if( !m_focusItem->isVisible() )
    {
        m_focusItem->show();

        return;
    }
    FieldPos focusPos = pixToField( m_focusItem->pos() );
    focusPos.x++;
    if (focusPos.x >= FIELD_SIZE)
        focusPos.x = 0;

    m_focusItem->setPos ( fieldToPix( focusPos ) );
}
