setMaxSourceCount(uint limit)
{
    if (d->limit == limit) {
        return;
    }

    d->limit = limit;

    if (d->limit > 0) {
        d->trimQueue();
    } else {
        d->sourceQueue.clear();
    }
}
