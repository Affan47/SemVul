replace_character(int c)
{
    int n = State;

    State = REPLACE;
    ins_char(c);
    State = n;

    dec_cursor();
}
