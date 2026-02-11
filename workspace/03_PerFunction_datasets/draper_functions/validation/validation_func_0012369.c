save(SavedProperties &p) const
{
    int count = 0;

    if (!m_usingTable) {
#if USE_SINGLE_ENTRY
        if (m_singleEntryKey && !(m_singleEntryAttributes & (ReadOnly | Function)))
            ++count;
#endif
    } else {
        int size = m_u.table->size;
        Entry *entries = m_u.table->entries;
        for (int i = 0; i != size; ++i)
            if (isValid(entries[i].key) && !(entries[i].attributes & (ReadOnly | Function)))
                ++count;
    }

    p._properties.clear();
    p._count = count;

    if (count == 0)
        return;

    p._properties.set(new SavedProperty [count]);

    SavedProperty *prop = p._properties.get();

    if (!m_usingTable) {
#if USE_SINGLE_ENTRY
        if (m_singleEntryKey && !(m_singleEntryAttributes & (ReadOnly | Function))) {
            prop->key = Identifier(m_singleEntryKey);
            prop->value = m_u.singleEntryValue;
            prop->attributes = m_singleEntryAttributes;
            ++prop;
        }
#endif
    } else {


        Vector<Entry*, smallMapThreshold> sortedEntries(count);


        Entry** p = sortedEntries.data();
        int size = m_u.table->size;
        Entry* entries = m_u.table->entries;
        for (int i = 0; i != size; ++i) {
            Entry *e = &entries[i];
            if (isValid(e->key) && !(e->attributes & (ReadOnly | Function)))
                *p++ = e;
        }
        assert(p - sortedEntries.data() == count);


        qsort(sortedEntries.data(), p - sortedEntries.data(), sizeof(Entry*), comparePropertyMapEntryIndices);


        for (Entry** q = sortedEntries.data(); q != p; ++q, ++prop) {
            Entry* e = *q;
            prop->key = Identifier(e->key);
            prop->value = e->value;
            prop->attributes = e->attributes;
        }
    }
}
