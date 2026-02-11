unlink()
{
    if (!d->exists) return;
    if (KTempDir::removeDir(d->tmpName))
        d->error=0;
    else
        d->error=errno;
    d->exists=false;
}
