replace_character(int c)
{
    int n = State;

    State = MODE_REPLACE;
    ins_char(c);
    State = n;

    dec_cursor();
}
