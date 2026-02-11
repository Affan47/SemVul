mouseMoveEvent ( QMouseEvent * event )
{

    bool state = isOverDeleteIcon ( event->pos() );
    if ( state != m_overDelete )
    {
        m_overDelete = state;
        this->update();
    }
}
