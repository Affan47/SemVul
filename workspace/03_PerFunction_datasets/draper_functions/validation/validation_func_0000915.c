setTextMarkers(s32 begin, s32 end)
{
    if ( begin != MarkBegin || end != MarkEnd )
    {
        MarkBegin = begin;
        MarkEnd = end;
        sendGuiEvent(EGET_EDITBOX_MARKING_CHANGED);
    }
}
