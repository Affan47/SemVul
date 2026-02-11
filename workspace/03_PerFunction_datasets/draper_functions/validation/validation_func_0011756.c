ntb_mail_parser_parse(struct ntb_mail_parser *parser,
                      const uint8_t *data,
                      size_t length,
                      struct ntb_error **error)
{
        ssize_t processed;

        while (length > 0) {
                switch (parser->state) {
                case NTB_MAIL_PARSER_HEADER_NAME:
                        processed = handle_header_name(parser,
                                                       data,
                                                       length,
                                                       error);
                        break;

                case NTB_MAIL_PARSER_HEADER_VALUE_START:
                        processed = handle_header_value_start(parser,
                                                              data,
                                                              length,
                                                              error);
                        break;

                case NTB_MAIL_PARSER_HEADER_VALUE:
                        processed = handle_header_value(parser,
                                                        data,
                                                        length,
                                                        error);
                        break;

                case NTB_MAIL_PARSER_CHECK_EOL:
                        processed = handle_check_eol(parser,
                                                     data,
                                                     length,
                                                     error);
                        break;

                case NTB_MAIL_PARSER_CHECK_CONTINUATION:
                        processed = handle_check_continuation(parser,
                                                              data,
                                                              length,
                                                              error);
                        break;

                case NTB_MAIL_PARSER_CONTENT:
                        processed = handle_content(parser, data, length, error);
                        break;
                }

                if (processed == -1)
                        return false;

                data += processed;
                length -= processed;
        }

        return true;
}
