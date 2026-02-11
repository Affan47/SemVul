FreeALConfig(void)
{
    unsigned int i;

    for(i = 0;i < cfgCount;i++)
    {
        unsigned int j;
        for(j = 0;j < cfgBlocks[i].entryCount;j++)
        {
           free(cfgBlocks[i].entries[j].key);
           free(cfgBlocks[i].entries[j].value);
        }
        free(cfgBlocks[i].entries);
        free(cfgBlocks[i].name);
    }
    free(cfgBlocks);
    cfgBlocks = NULL;
    cfgCount = 0;
}
