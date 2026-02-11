getEntryPoint(le_int32 index, LEPoint &entryPoint) const
{
    if (fEntryExitPoints == NULL) {
        return NULL;
    }

    return fEntryExitPoints[index].getEntryPoint(entryPoint);
}
