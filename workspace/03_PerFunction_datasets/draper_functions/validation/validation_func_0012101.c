ins_a_note()
{
    long the_dur = (trunc(dur) * artic + 50) / 100;
    int the_pitch = pitch;
    event_type note;
    if (rest_flag) the_pitch = NO_PITCH;
    note = insert_note(the_score, seqround(thetime), lineno, voice,
                       the_pitch, the_dur, loud);
    if (!note) return FALSE;
    return TRUE;
}
