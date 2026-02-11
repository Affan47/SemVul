Set(const double array[])
{
    bool changed = false;
    for (int i = 0; i < Size(); i++)
        changed |= ufnumberarray->SilentChange(this, i, array[i]);
    if (changed)
        ufnumberarray->CallValueChangedEvent(this);
}
