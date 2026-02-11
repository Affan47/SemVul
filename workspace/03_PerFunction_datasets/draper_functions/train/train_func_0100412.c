currentDir() const
{
    if( d->currentPath.isLocalFile() )
        return d->currentPath.toLocalFile();
    else
        return d->currentPath.url();
}
