UnloadScriptLibrary()
{
    if (!m_hScriptLib)
        return;

    if (m_pOnFreeScriptLibrary)
        m_pOnFreeScriptLibrary();

    MANGOS_CLOSE_LIBRARY(m_hScriptLib);
    m_hScriptLib = NULL;

    m_pOnInitScriptLibrary      = NULL;
    m_pOnFreeScriptLibrary      = NULL;
    m_pGetScriptLibraryVersion  = NULL;

    m_pGetCreatureAI            = NULL;
    m_pCreateInstanceData       = NULL;

    m_pOnGossipHello            = NULL;
    m_pOnGOGossipHello          = NULL;
    m_pOnGossipSelect           = NULL;
    m_pOnGOGossipSelect         = NULL;
    m_pOnGossipSelectWithCode   = NULL;
    m_pOnGOGossipSelectWithCode = NULL;
    m_pOnQuestAccept            = NULL;
    m_pOnGOQuestAccept          = NULL;
    m_pOnItemQuestAccept        = NULL;
    m_pOnQuestRewarded          = NULL;
    m_pOnGOQuestRewarded        = NULL;
    m_pGetNPCDialogStatus       = NULL;
    m_pGetGODialogStatus        = NULL;
    m_pOnGOUse                  = NULL;
    m_pOnItemUse                = NULL;
    m_pOnAreaTrigger            = NULL;
    m_pOnNpcSpellClick          = NULL;
    m_pOnProcessEvent           = NULL;
    m_pOnEffectDummyCreature    = NULL;
    m_pOnEffectDummyGO          = NULL;
    m_pOnEffectDummyItem        = NULL;
    m_pOnEffectScriptEffectCreature = NULL;
    m_pOnAuraDummy              = NULL;
}
