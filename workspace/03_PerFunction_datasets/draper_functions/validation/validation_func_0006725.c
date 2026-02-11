MetaEvent ( MIDIClockTime time, int type, int leng, unsigned char *m )
{
    switch ( type )
    {
    case MF_META_GENERIC_TEXT:
    case MF_META_COPYRIGHT:
    case MF_META_TRACK_NAME:
    case MF_META_INSTRUMENT_NAME:
    case MF_META_LYRIC_TEXT:
    case MF_META_MARKER_TEXT:
    case MF_META_CUE_POINT:
    case MF_META_GENERIC_TEXT_8:
    case MF_META_GENERIC_TEXT_9:
    case MF_META_GENERIC_TEXT_A:
    case MF_META_GENERIC_TEXT_B:
    case MF_META_GENERIC_TEXT_C:
    case MF_META_GENERIC_TEXT_D:
    case MF_META_GENERIC_TEXT_E:
    case MF_META_GENERIC_TEXT_F:

        m[leng] = '\0';
        return mf_text ( time, type, leng, m );

    case MF_META_END_OF_TRACK:
        return mf_eot ( time );

    case MF_META_TEMPO:
        return mf_tempo ( time, m[0], m[1], m[2] );

    case MF_META_TIMESIG:
        return mf_timesig ( time, m[0], m[1], m[2], m[3] );

    case MF_META_KEYSIG:
        return mf_keysig ( time, (char) m[0], m[1] );

    case MF_META_SEQUENCER_SPECIFIC:
        return mf_sqspecific ( time, leng, m );

    case MF_META_SEQUENCE_NUMBER:
    case MF_META_SMPTE:
    case MF_META_TRACK_LOOP:
    case MF_META_OUTPUT_CABLE:
    case MF_META_CHANNEL_PREFIX:
    default:
        return mf_metamisc ( time, type, leng, m );
        break;
    }
    return true;
}
