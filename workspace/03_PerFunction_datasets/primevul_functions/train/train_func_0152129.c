yaml_parser_fetch_next_token(yaml_parser_t *parser)
{


    if (!CACHE(parser, 1))
        return 0;


    if (!parser->stream_start_produced)
        return yaml_parser_fetch_stream_start(parser);


    if (!yaml_parser_scan_to_next_token(parser))
        return 0;


    if (!yaml_parser_stale_simple_keys(parser))
        return 0;


    if (!yaml_parser_unroll_indent(parser, parser->mark.column))
        return 0;


    if (!CACHE(parser, 4))
        return 0;


    if (IS_Z(parser->buffer))
        return yaml_parser_fetch_stream_end(parser);


    if (parser->mark.column == 0 && CHECK(parser->buffer, '%'))
        return yaml_parser_fetch_directive(parser);


    if (parser->mark.column == 0
            && CHECK_AT(parser->buffer, '-', 0)
            && CHECK_AT(parser->buffer, '-', 1)
            && CHECK_AT(parser->buffer, '-', 2)
            && IS_BLANKZ_AT(parser->buffer, 3))
        return yaml_parser_fetch_document_indicator(parser,
                YAML_DOCUMENT_START_TOKEN);


    if (parser->mark.column == 0
            && CHECK_AT(parser->buffer, '.', 0)
            && CHECK_AT(parser->buffer, '.', 1)
            && CHECK_AT(parser->buffer, '.', 2)
            && IS_BLANKZ_AT(parser->buffer, 3))
        return yaml_parser_fetch_document_indicator(parser,
                YAML_DOCUMENT_END_TOKEN);


    if (CHECK(parser->buffer, '['))
        return yaml_parser_fetch_flow_collection_start(parser,
                YAML_FLOW_SEQUENCE_START_TOKEN);


    if (CHECK(parser->buffer, '{'))
        return yaml_parser_fetch_flow_collection_start(parser,
                YAML_FLOW_MAPPING_START_TOKEN);


    if (CHECK(parser->buffer, ']'))
        return yaml_parser_fetch_flow_collection_end(parser,
                YAML_FLOW_SEQUENCE_END_TOKEN);


    if (CHECK(parser->buffer, '}'))
        return yaml_parser_fetch_flow_collection_end(parser,
                YAML_FLOW_MAPPING_END_TOKEN);


    if (CHECK(parser->buffer, ','))
        return yaml_parser_fetch_flow_entry(parser);


    if (CHECK(parser->buffer, '-') && IS_BLANKZ_AT(parser->buffer, 1))
        return yaml_parser_fetch_block_entry(parser);


    if (CHECK(parser->buffer, '?')
            && (parser->flow_level || IS_BLANKZ_AT(parser->buffer, 1)))
        return yaml_parser_fetch_key(parser);


    if (CHECK(parser->buffer, ':')
            && (parser->flow_level || IS_BLANKZ_AT(parser->buffer, 1)))
        return yaml_parser_fetch_value(parser);


    if (CHECK(parser->buffer, '*'))
        return yaml_parser_fetch_anchor(parser, YAML_ALIAS_TOKEN);


    if (CHECK(parser->buffer, '&'))
        return yaml_parser_fetch_anchor(parser, YAML_ANCHOR_TOKEN);


    if (CHECK(parser->buffer, '!'))
        return yaml_parser_fetch_tag(parser);


    if (CHECK(parser->buffer, '|') && !parser->flow_level)
        return yaml_parser_fetch_block_scalar(parser, 1);


    if (CHECK(parser->buffer, '>') && !parser->flow_level)
        return yaml_parser_fetch_block_scalar(parser, 0);


    if (CHECK(parser->buffer, '\''))
        return yaml_parser_fetch_flow_scalar(parser, 1);


    if (CHECK(parser->buffer, '"'))
        return yaml_parser_fetch_flow_scalar(parser, 0);


    if (!(IS_BLANKZ(parser->buffer) || CHECK(parser->buffer, '-')
                || CHECK(parser->buffer, '?') || CHECK(parser->buffer, ':')
                || CHECK(parser->buffer, ',') || CHECK(parser->buffer, '[')
                || CHECK(parser->buffer, ']') || CHECK(parser->buffer, '{')
                || CHECK(parser->buffer, '}') || CHECK(parser->buffer, '#')
                || CHECK(parser->buffer, '&') || CHECK(parser->buffer, '*')
                || CHECK(parser->buffer, '!') || CHECK(parser->buffer, '|')
                || CHECK(parser->buffer, '>') || CHECK(parser->buffer, '\'')
                || CHECK(parser->buffer, '"') || CHECK(parser->buffer, '%')
                || CHECK(parser->buffer, '@') || CHECK(parser->buffer, '`')) ||
            (CHECK(parser->buffer, '-') && !IS_BLANK_AT(parser->buffer, 1)) ||
            (!parser->flow_level &&
             (CHECK(parser->buffer, '?') || CHECK(parser->buffer, ':'))
             && !IS_BLANKZ_AT(parser->buffer, 1)))
        return yaml_parser_fetch_plain_scalar(parser);


    return yaml_parser_set_scanner_error(parser,
            "while scanning for the next token", parser->mark,
            "found character that cannot start any token");
}
