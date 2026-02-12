yaml_parser_fetch_value(yaml_parser_t *parser)
{
    yaml_mark_t start_mark, end_mark;
    yaml_token_t token;
    yaml_simple_key_t *simple_key = parser->simple_keys.top-1;


    if (simple_key->possible)
    {


        TOKEN_INIT(token, YAML_KEY_TOKEN, simple_key->mark, simple_key->mark);

        if (!QUEUE_INSERT(parser, parser->tokens,
                    simple_key->token_number - parser->tokens_parsed, token))
            return 0;


        if (!yaml_parser_roll_indent(parser, simple_key->mark.column,
                    simple_key->token_number,
                    YAML_BLOCK_MAPPING_START_TOKEN, simple_key->mark))
            return 0;


        simple_key->possible = 0;


        parser->simple_key_allowed = 0;
    }
    else
    {


        if (!parser->flow_level)
        {


            if (!parser->simple_key_allowed) {
                return yaml_parser_set_scanner_error(parser, NULL, parser->mark,
                        "mapping values are not allowed in this context");
            }


            if (!yaml_parser_roll_indent(parser, parser->mark.column, -1,
                        YAML_BLOCK_MAPPING_START_TOKEN, parser->mark))
                return 0;
        }


        parser->simple_key_allowed = (!parser->flow_level);
    }


    start_mark = parser->mark;
    SKIP(parser);
    end_mark = parser->mark;


    TOKEN_INIT(token, YAML_VALUE_TOKEN, start_mark, end_mark);

    if (!ENQUEUE(parser, parser->tokens, token))
        return 0;

    return 1;
}
