static void remove_entry(HashEntry* entry)
{
    HashEntry* prev = entry->prev;
    HashEntry* next = entry->next;

    if (prev != NULL) entry->prev->next = next;
    if (next != NULL) entry->next->prev = prev;

    if (prev == NULL) {

        gHashTable.slots[entry->slot] = entry->next;
    }


    gHashTable.count--;
}
