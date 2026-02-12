AP4_AudioSampleEntry::ToSampleDescription()
{

    return new AP4_GenericAudioSampleDescription(
        m_Type,
        GetSampleRate(),
        GetSampleSize(),
        GetChannelCount(),
        this);
}
