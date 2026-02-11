GetConfigValue(const char *blockName, const char *keyName, const char *def)
{
    unsigned int i, j;

    if(!keyName)
        return def;

    if(!blockName)
        blockName = "general";

    for(i = 0;i < cfgCount;i++)
    {
        if(strcasecmp(cfgBlocks[i].name, blockName) != 0)
            continue;

        for(j = 0;j < cfgBlocks[i].entryCount;j++)
        {
            if(strcasecmp(cfgBlocks[i].entries[j].key, keyName) == 0)
            {
                TRACE("Found %s:%s = \"%s\"\n", blockName, keyName,
                      cfgBlocks[i].entries[j].value);
                if(cfgBlocks[i].entries[j].value[0])
                    return cfgBlocks[i].entries[j].value;
                return def;
            }
        }
    }

    TRACE("Key %s:%s not found\n", blockName, keyName);
    return def;
}
