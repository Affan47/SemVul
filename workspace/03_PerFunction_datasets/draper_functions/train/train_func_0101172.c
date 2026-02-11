_parse_encode(instance_t *instance,xmlDocPtr doc, xmlNodePtr node)
{
    instance->encode = 1;
    do {
        if (node == NULL) break;
        if (xmlIsBlankNode(node)) continue;

        if (strcmp(node->name, "nominal-bitrate") == 0)
            SET_INT(instance->nom_br);
        else if (strcmp(node->name, "minimum-bitrate") == 0)
            SET_INT(instance->min_br);
        else if (strcmp(node->name, "maximum-bitrate") == 0)
            SET_INT(instance->max_br);
        else if (strcmp(node->name, "quality") == 0)
            SET_FLOAT(instance->quality);
        else if (strcmp(node->name, "samplerate") == 0)
            SET_INT(instance->samplerate);
        else if (strcmp(node->name, "channels") == 0)
            SET_INT(instance->channels);
        else if (strcmp(node->name, "managed") == 0)
            SET_INT(instance->managed);
        else if (strcmp(node->name, "flush-samples") == 0)
            SET_INT(instance->max_samples_ppage);
    } while ((node = node->next));
    if (instance->max_samples_ppage == 0)
        instance->max_samples_ppage = instance->samplerate;
    if (instance->max_samples_ppage < instance->samplerate/100)
        instance->max_samples_ppage = instance->samplerate/100;
}
