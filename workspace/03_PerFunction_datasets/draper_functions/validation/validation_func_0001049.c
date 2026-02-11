CfgNext(int WhichCfg, ConfigEntryT ** last)


{
    if (last == NULL)
        return (ConfigEntryT **) configinfo[WhichCfg].config_info;

    last++;
    if (last > (ConfigEntryT **) configinfo[WhichCfg].config_info + configinfo[WhichCfg].config_info_size - 1)
        return NULL;

    return last;
}
