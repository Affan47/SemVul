RemoveAllInvite()
{
    CalendarInviteMap::iterator itr = m_Invitee.begin();
    while (itr != m_Invitee.end())
        RemoveInviteByItr(itr++);
}
