_clearReferenceCounters(FWObject *o)
{
    o->clearRefCounter();
    for (FWObject::iterator i=o->begin(); i!=o->end(); ++i)
    {
        _clearReferenceCounters(*i);
    }
}
