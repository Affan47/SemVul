yaml_parser_increase_flow_level(yaml_parser_t *parser)
{
    yaml_simple_key_t empty_simple_key = { 0, 0, 0, { 0, 0, 0 } };


    if (!PUSH(parser, parser->simple_keys, empty_simple_key))
        return 0;


    if (parser->flow_level == INT_MAX) {
        parser->error = YAML_MEMORY_ERROR;
        return 0;
    }

    parser->flow_level++;

    return 1;
}
