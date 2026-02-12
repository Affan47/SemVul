yaml_parser_fetch_more_tokens(yaml_parser_t *parser)
{
    int need_more_tokens;


    while (1)
    {


        need_more_tokens = 0;

        if (parser->tokens.head == parser->tokens.tail)
        {


            need_more_tokens = 1;
        }
        else
        {
            yaml_simple_key_t *simple_key;


            if (!yaml_parser_stale_simple_keys(parser))
                return 0;

            for (simple_key = parser->simple_keys.start;
                    simple_key != parser->simple_keys.top; simple_key++) {
                if (simple_key->possible
                        && simple_key->token_number == parser->tokens_parsed) {
                    need_more_tokens = 1;
                    break;
                }
            }
        }


        if (!need_more_tokens)
            break;


        if (!yaml_parser_fetch_next_token(parser))
            return 0;
    }

    parser->token_available = 1;

    return 1;
}
