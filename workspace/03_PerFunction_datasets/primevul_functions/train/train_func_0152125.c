yaml_parser_fetch_stream_start(yaml_parser_t *parser)
{
    yaml_simple_key_t simple_key = { 0, 0, 0, { 0, 0, 0 } };
    yaml_token_t token;


    parser->indent = -1;


    if (!PUSH(parser, parser->simple_keys, simple_key))
        return 0;


    parser->simple_key_allowed = 1;


    parser->stream_start_produced = 1;


    STREAM_START_TOKEN_INIT(token, parser->encoding,
            parser->mark, parser->mark);

    if (!ENQUEUE(parser, parser->tokens, token))
        return 0;

    return 1;
}
