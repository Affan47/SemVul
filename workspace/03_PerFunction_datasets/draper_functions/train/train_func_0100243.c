findExactEntry(const QByteArray& group, const QByteArray& key, KEntryMap::SearchFlags flags)
{
    KEntryKey theKey(group, key, bool(flags&SearchLocalized), bool(flags&SearchDefaults));
    return find(theKey);
}
