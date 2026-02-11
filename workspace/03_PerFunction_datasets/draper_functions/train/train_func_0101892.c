plist_data_hash(gconstpointer key)
{
    plist_data_t data = plist_get_data((plist_t) key);

    guint hash = data->type;
    guint i = 0;

    char *buff = NULL;
    guint size = 0;

    switch (data->type)
    {
    case PLIST_BOOLEAN:
    case PLIST_UINT:
    case PLIST_REAL:
        buff = (char *) &data->intval;
        size = 8;
        break;
    case PLIST_KEY:
    case PLIST_STRING:
        buff = data->strval;
        size = strlen(buff);
        break;
    case PLIST_DATA:
    case PLIST_ARRAY:
    case PLIST_DICT:

        buff = (char *) &key;
        size = sizeof(gconstpointer);
        break;
    case PLIST_DATE:
        buff = (char *) &(data->timeval);
        size = data->length;
        break;
    default:
        break;
    }


    for (i = 0; i < size; buff++, i++)
        hash = hash << 7 ^ (*buff);

    return hash;
}
