updateWonItem()
{
    const qreal aspectRatio = Renderer::self()->aspectRatioOfElement("message_frame");
    int boxWidth;
    int boxHeight;
    if ( width() < aspectRatio * height() )
    {
        boxWidth = width() * wonBoxToSceneSizeRatio;
        boxHeight = boxWidth / aspectRatio;
    }
    else
    {
        boxHeight = height() * wonBoxToSceneSizeRatio;
        boxWidth = boxHeight * aspectRatio;
    }
    m_wonItem->setSize( QSize( boxWidth, boxHeight ) );

    if ( m_playerReceivedHelp )
        m_wonItem->setMessage( i18n( "Congratulations! We have won." ) );
    else
        m_wonItem->setMessage( i18n( "Congratulations! You have won." ) );

    m_wonItem->setPos( QPointF( (width() - boxWidth) / 2, (height() - boxHeight) / 2 )
                        + sceneRect().topLeft() );
}
