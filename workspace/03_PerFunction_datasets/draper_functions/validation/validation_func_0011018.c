detachCounters()
{
    QHash<DOMString,khtml::CounterNode*>* counters = document()->counters(this);
    if (!counters) return;

    QHashIterator<DOMString,khtml::CounterNode*> i(*counters);

    while (i.hasNext()) {
        i.next();
        i.value()->remove();
        delete i.value();
    }
    document()->removeCounters(this);
}
