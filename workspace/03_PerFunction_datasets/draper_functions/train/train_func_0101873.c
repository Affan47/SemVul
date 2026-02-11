us_osc_multisender_can_send( us_osc_sender_t *self_ )
{
    bool r = false;
    us_osc_multisender_t *self = (us_osc_multisender_t *)self_;
    us_osc_multisender_item_t *item = self->m_first_item;
    if ( item )
    {

        r = true;
    }
    while ( item )
    {
        if ( item->m_sender )
        {
            r &= item->m_sender->can_send( item->m_sender );
        }
        item = item->m_next;
    }
    return r;
}
