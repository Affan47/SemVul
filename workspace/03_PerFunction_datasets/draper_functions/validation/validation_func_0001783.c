executedCount()
{
    if (_dirty) update();

    return _executedCount;
}
