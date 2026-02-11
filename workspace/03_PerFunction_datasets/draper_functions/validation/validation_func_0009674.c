effect_insert (PluginHandle * plugin, EffectPlugin * header)
{
    if (g_list_find_custom (running_effects, plugin, (GCompareFunc)
     effect_find_cb) != NULL)
        return;

    AUDDBG ("Adding %s without reset.\n", plugin_get_name (plugin));
    RunningEffect * effect = g_malloc (sizeof (RunningEffect));
    effect->plugin = plugin;
    effect->header = header;
    effect->remove_flag = FALSE;

    running_effects = g_list_insert_sorted (running_effects, effect,
     (GCompareFunc) effect_compare);
    GList * node = g_list_find (running_effects, effect);

    int channels, rate;
    if (node->prev != NULL)
    {
        RunningEffect * prev = node->prev->data;
        AUDDBG ("Added %s after %s.\n", plugin_get_name (plugin),
         plugin_get_name (prev->plugin));
        channels = prev->channels_returned;
        rate = prev->rate_returned;
    }
    else
    {
        AUDDBG ("Added %s as first effect.\n", plugin_get_name (plugin));
        channels = input_channels;
        rate = input_rate;
    }

    AUDDBG ("Starting %s at %d channels, %d Hz.\n", plugin_get_name (plugin),
     channels, rate);
    header->start (& channels, & rate);
    effect->channels_returned = channels;
    effect->rate_returned = rate;
}
