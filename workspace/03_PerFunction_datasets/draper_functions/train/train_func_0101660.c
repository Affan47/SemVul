cr_parser_parse_declaration_core (CRParser * a_this)
{
        CRToken *token = NULL;
        CRInputPos init_pos;
        enum CRStatus status = CR_ERROR;
        CRString *prop = NULL;

        g_return_val_if_fail (a_this && PRIVATE (a_this), CR_BAD_PARAM_ERROR);

        RECORD_INITIAL_POS (a_this, &init_pos);

        status = cr_parser_parse_property (a_this, &prop);
        CHECK_PARSING_STATUS (status, FALSE);
        cr_parser_clear_errors (a_this);
        ENSURE_PARSING_COND (status == CR_OK && prop);
        cr_string_destroy (prop);
        prop = NULL;

        status = cr_tknzr_get_next_token (PRIVATE (a_this)->tknzr, &token);
        ENSURE_PARSING_COND (status == CR_OK
                             && token
                             && token->type == DELIM_TK
                             && token->u.unichar == ':');
        cr_token_destroy (token);
        token = NULL;
        cr_parser_try_to_skip_spaces_and_comments (a_this);
        status = cr_parser_parse_value_core (a_this);
        CHECK_PARSING_STATUS (status, FALSE);

        return CR_OK;

      error:

        if (prop) {
                cr_string_destroy (prop);
                prop = NULL;
        }

        if (token) {
                cr_token_destroy (token);
                token = NULL;
        }

        cr_tknzr_set_cur_pos (PRIVATE (a_this)->tknzr, &init_pos);

        return status;
}
