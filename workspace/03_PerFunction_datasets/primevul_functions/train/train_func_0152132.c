yaml_parser_scan_tag(yaml_parser_t *parser, yaml_token_t *token)
{
    yaml_char_t *handle = NULL;
    yaml_char_t *suffix = NULL;
    yaml_mark_t start_mark, end_mark;

    start_mark = parser->mark;


    if (!CACHE(parser, 2)) goto error;

    if (CHECK_AT(parser->buffer, '<', 1))
    {


        handle = yaml_malloc(1);
        if (!handle) goto error;
        handle[0] = '\0';


        SKIP(parser);
        SKIP(parser);


        if (!yaml_parser_scan_tag_uri(parser, 0, NULL, start_mark, &suffix))
            goto error;


        if (!CHECK(parser->buffer, '>')) {
            yaml_parser_set_scanner_error(parser, "while scanning a tag",
                    start_mark, "did not find the expected '>'");
            goto error;
        }

        SKIP(parser);
    }
    else
    {


        if (!yaml_parser_scan_tag_handle(parser, 0, start_mark, &handle))
            goto error;


        if (handle[0] == '!' && handle[1] != '\0' && handle[strlen((char *)handle)-1] == '!')
        {


            if (!yaml_parser_scan_tag_uri(parser, 0, NULL, start_mark, &suffix))
                goto error;
        }
        else
        {


            if (!yaml_parser_scan_tag_uri(parser, 0, handle, start_mark, &suffix))
                goto error;


            yaml_free(handle);
            handle = yaml_malloc(2);
            if (!handle) goto error;
            handle[0] = '!';
            handle[1] = '\0';


            if (suffix[0] == '\0') {
                yaml_char_t *tmp = handle;
                handle = suffix;
                suffix = tmp;
            }
        }
    }


    if (!CACHE(parser, 1)) goto error;

    if (!IS_BLANKZ(parser->buffer)) {
        yaml_parser_set_scanner_error(parser, "while scanning a tag",
                start_mark, "did not find expected whitespace or line break");
        goto error;
    }

    end_mark = parser->mark;


    TAG_TOKEN_INIT(*token, handle, suffix, start_mark, end_mark);

    return 1;

error:
    yaml_free(handle);
    yaml_free(suffix);
    return 0;
}
