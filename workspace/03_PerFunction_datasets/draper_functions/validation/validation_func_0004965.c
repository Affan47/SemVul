finalize()
{
    if( d->script )
        emit finalized(this);
    delete d->script;
    d->script = 0;
}
