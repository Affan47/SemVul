xaccTransCountSplits (const Transaction *trans)
{
    gint i = 0;
    FOR_EACH_SPLIT(trans, i++);
    return i;
}
