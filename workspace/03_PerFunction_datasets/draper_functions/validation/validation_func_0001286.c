mousePressEvent( QMouseEvent *e )
{
    m_pressedPos = e->pos();
    if( m_arrowRect.contains( m_pressedPos ) )
        m_arrowPressed = true;
    else
    {
        m_arrowPressed = false;
        BreadcrumbItemButton::mousePressEvent( e );
    }
}
