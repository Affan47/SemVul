ProcessWhiteNote ( int in_note, int *out_note )
{
    ENTER ( "MIDIKeySignature::ProcessWhiteNote()" );


    if ( state[in_note] == ACCNatural )
    {


        *out_note = in_note;


        return false;
    }

    else
    {


        *out_note = in_note;


        state[in_note] = ACCNatural;


        return true;
    }
}
