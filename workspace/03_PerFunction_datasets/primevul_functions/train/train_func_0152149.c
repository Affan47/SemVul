yaml_parser_fetch_plain_scalar(yaml_parser_t *parser)
{
    yaml_token_t token;


    if (!yaml_parser_save_simple_key(parser))
        return 0;


    parser->simple_key_allowed = 0;


    if (!yaml_parser_scan_plain_scalar(parser, &token))
        return 0;

    if (!ENQUEUE(parser, parser->tokens, token)) {
        yaml_token_delete(&token);
        return 0;
    }

    return 1;
}
