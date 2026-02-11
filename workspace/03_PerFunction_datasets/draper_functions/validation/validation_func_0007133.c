OnRelease()
{
    if ( !IsAttached() )
        return;

    Manager::Get()->RemoveAllEventSinksFor(this);

    if (m_Html)
        m_Html->Destroy();
    m_Html = 0;

    if (m_Popup)
        m_Popup->Destroy();
    m_Popup = 0;
}
