yaml_parser_scan(yaml_parser_t *parser, yaml_token_t *token)
{
    assert(parser);
    assert(token);


    memset(token, 0, sizeof(yaml_token_t));


    if (parser->stream_end_produced || parser->error) {
        return 1;
    }


    if (!parser->token_available) {
        if (!yaml_parser_fetch_more_tokens(parser))
            return 0;
    }


    *token = DEQUEUE(parser, parser->tokens);
    parser->token_available = 0;
    parser->tokens_parsed ++;

    if (token->type == YAML_STREAM_END_TOKEN) {
        parser->stream_end_produced = 1;
    }

    return 1;
}
