null_scale(double x, double y)
{
    (void) x;
    (void) y;
    int_error(NO_CARET, "Attempt to call deprecated terminal function");
    return FALSE;
}
