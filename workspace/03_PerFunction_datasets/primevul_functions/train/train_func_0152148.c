yaml_parser_fetch_stream_end(yaml_parser_t *parser)
{
    yaml_token_t token;


    if (parser->mark.column != 0) {
        parser->mark.column = 0;
        parser->mark.line ++;
    }


    if (!yaml_parser_unroll_indent(parser, -1))
        return 0;


    if (!yaml_parser_remove_simple_key(parser))
        return 0;

    parser->simple_key_allowed = 0;


    STREAM_END_TOKEN_INIT(token, parser->mark, parser->mark);

    if (!ENQUEUE(parser, parser->tokens, token))
        return 0;

    return 1;
}
