yaml_parser_fetch_flow_entry(yaml_parser_t *parser)
{
    yaml_mark_t start_mark, end_mark;
    yaml_token_t token;


    if (!yaml_parser_remove_simple_key(parser))
        return 0;


    parser->simple_key_allowed = 1;


    start_mark = parser->mark;
    SKIP(parser);
    end_mark = parser->mark;


    TOKEN_INIT(token, YAML_FLOW_ENTRY_TOKEN, start_mark, end_mark);

    if (!ENQUEUE(parser, parser->tokens, token))
        return 0;

    return 1;
}
