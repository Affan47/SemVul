Setting_get_int(const char *key, int def)
{
    bstring value = tst_search(SETTINGS_MAP, key, strlen(key));

    if(value) {
        return atoi((const char *)value->data);
    } else {
        return def;
    }
}
