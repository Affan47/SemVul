Event_ViewPointVisibilityChanged()
{
    if (!m_owner.HaveAtClient(m_source))
        ResetView();
}
