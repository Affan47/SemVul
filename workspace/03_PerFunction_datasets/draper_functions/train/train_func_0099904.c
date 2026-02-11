propertyExists(const QString &key) const
{
    d->checkCache(key);
    return d->cache.value(key).isValid();
}
