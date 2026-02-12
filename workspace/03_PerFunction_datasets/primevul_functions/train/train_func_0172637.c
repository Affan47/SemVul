void Parser::ReduceDeferredScriptLength(size_t chars)
{


    if ((m_grfscr & fscrDeferFncParse) &&
        (
            PHASE_OFF1(Js::DeferEventHandlersPhase) ||
            (m_grfscr & fscrGlobalCode)
        )
    )
    {
        if (m_length > chars)
        {
            m_length -= chars;
        }
        else
        {
            m_length = 0;
        }
        if (m_length < Parser::GetDeferralThreshold(this->m_sourceContextInfo->IsSourceProfileLoaded()))
        {

            m_grfscr &= ~fscrDeferFncParse;
            m_stoppedDeferredParse = TRUE;
        }
    }
}
