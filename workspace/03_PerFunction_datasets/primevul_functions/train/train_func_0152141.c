yaml_parser_unroll_indent(yaml_parser_t *parser, ptrdiff_t column)
{
    yaml_token_t token;


    if (parser->flow_level)
        return 1;


    while (parser->indent > column)
    {


        TOKEN_INIT(token, YAML_BLOCK_END_TOKEN, parser->mark, parser->mark);

        if (!ENQUEUE(parser, parser->tokens, token))
            return 0;


        parser->indent = POP(parser, parser->indents);
    }

    return 1;
}
