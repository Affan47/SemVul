static HashEntry* find_entry(HashTable* table, int slot,
        intptr_t* backtrace, size_t numEntries, size_t size)
{
    HashEntry* entry = table->slots[slot];
    while (entry != NULL) {


        if (entry->size == size && entry->numEntries == numEntries &&
                !memcmp(backtrace, entry->backtrace, numEntries * sizeof(intptr_t))) {
            return entry;
        }

        entry = entry->next;
    }

    return NULL;
}
