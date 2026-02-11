HandleEvent(uint32 eventId, GameObject* go)
{

    if (go->GetEntry() != GO_HALAA_BANNER)
        return false;

    bool eventHandled = true;

    switch (eventId)
    {
        case EVENT_HALAA_BANNER_WIN_ALLIANCE:
            ProcessCaptureEvent(go, ALLIANCE);
            eventHandled = false;
            break;
        case EVENT_HALAA_BANNER_WIN_HORDE:
            ProcessCaptureEvent(go, HORDE);
            eventHandled = false;
            break;
        case EVENT_HALAA_BANNER_PROGRESS_ALLIANCE:
            SetBannerVisual(go, CAPTURE_ARTKIT_ALLIANCE, CAPTURE_ANIM_ALLIANCE);
            sWorld.SendDefenseMessage(ZONE_ID_NAGRAND, LANG_OPVP_NA_PROGRESS_A);
            break;
        case EVENT_HALAA_BANNER_PROGRESS_HORDE:
            SetBannerVisual(go, CAPTURE_ARTKIT_HORDE, CAPTURE_ANIM_HORDE);
            sWorld.SendDefenseMessage(ZONE_ID_NAGRAND, LANG_OPVP_NA_PROGRESS_H);
            break;
    }


    return eventHandled;
}
