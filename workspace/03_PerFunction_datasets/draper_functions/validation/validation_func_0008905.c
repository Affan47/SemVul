Ns_SetPutValue(Ns_Set *set, int index, char *value)
{
    if ((index != -1) && (index < set->size)) {
        ns_free(set->fields[index].value);
        set->fields[index].value = ns_strcopy(value);
    }
}
