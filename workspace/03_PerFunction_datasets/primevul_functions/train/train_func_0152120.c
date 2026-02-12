yaml_parser_scan_to_next_token(yaml_parser_t *parser)
{


    while (1)
    {


        if (!CACHE(parser, 1)) return 0;

        if (parser->mark.column == 0 && IS_BOM(parser->buffer))
            SKIP(parser);


        if (!CACHE(parser, 1)) return 0;

        while (CHECK(parser->buffer,' ') ||
                ((parser->flow_level || !parser->simple_key_allowed) &&
                 CHECK(parser->buffer, '\t'))) {
            SKIP(parser);
            if (!CACHE(parser, 1)) return 0;
        }


        if (CHECK(parser->buffer, '#')) {
            while (!IS_BREAKZ(parser->buffer)) {
                SKIP(parser);
                if (!CACHE(parser, 1)) return 0;
            }
        }


        if (IS_BREAK(parser->buffer))
        {
            if (!CACHE(parser, 2)) return 0;
            SKIP_LINE(parser);


            if (!parser->flow_level) {
                parser->simple_key_allowed = 1;
            }
        }
        else
        {


            break;
        }
    }

    return 1;
}
