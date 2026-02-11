SetSuppressSlots(bool b, bool force)
{
    if (mSuppressSlots == b && !force)
    {
        return false;
    }
    mSuppressSlots = b;
    return true;
}
