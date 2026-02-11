isEditableColumn( Column c )
{
    return c == Album ||
        c == Artist ||
        c == Comment ||
        c == Composer ||
        c == DiscNumber ||
        c == Genre ||
        c == Rating ||
        c == Title ||
        c == TitleWithTrackNum ||
        c == TrackNumber ||
        c == Year ||
        c == Bpm;
}
