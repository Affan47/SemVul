scanner_scan_primary_expression (parser_context_t *context_p,
                                 scanner_context_t *scanner_context_p,
                                 lexer_token_type_t type,
                                 scan_stack_modes_t stack_top)
{
  switch (type)
  {
    case LEXER_KEYW_NEW:
    {
      scanner_context_p->mode = SCAN_MODE_PRIMARY_EXPRESSION_AFTER_NEW;

#if ENABLED (JERRY_ES2015)
      if (scanner_try_scan_new_target (context_p))
      {
        scanner_context_p->mode = SCAN_MODE_POST_PRIMARY_EXPRESSION;
      }
#endif
      break;
    }
    case LEXER_DIVIDE:
    case LEXER_ASSIGN_DIVIDE:
    {
      lexer_construct_regexp_object (context_p, true);
      scanner_context_p->mode = SCAN_MODE_POST_PRIMARY_EXPRESSION;
      break;
    }
    case LEXER_KEYW_FUNCTION:
    {
      uint16_t status_flags = SCANNER_LITERAL_POOL_FUNCTION;

#if ENABLED (JERRY_ES2015)
      if (scanner_context_p->async_source_p != NULL)
      {
        status_flags |= SCANNER_LITERAL_POOL_ASYNC;
      }

      if (lexer_consume_generator (context_p))
      {
        status_flags |= SCANNER_LITERAL_POOL_GENERATOR;
      }
#endif

      scanner_push_literal_pool (context_p, scanner_context_p, status_flags);

      lexer_next_token (context_p);

      if (context_p->token.type == LEXER_LITERAL
          && context_p->token.lit_location.type == LEXER_IDENT_LITERAL)
      {
        lexer_next_token (context_p);
      }

      parser_stack_push_uint8 (context_p, SCAN_STACK_FUNCTION_EXPRESSION);
      scanner_context_p->mode = SCAN_MODE_FUNCTION_ARGUMENTS;
      return SCAN_KEEP_TOKEN;
    }
    case LEXER_LEFT_PAREN:
    {
      scanner_scan_bracket (context_p, scanner_context_p);
      return SCAN_KEEP_TOKEN;
    }
    case LEXER_LEFT_SQUARE:
    {
#if ENABLED (JERRY_ES2015)
      scanner_push_destructuring_pattern (context_p, scanner_context_p, SCANNER_BINDING_NONE, false);
#endif

      parser_stack_push_uint8 (context_p, SCAN_STACK_ARRAY_LITERAL);
      scanner_context_p->mode = SCAN_MODE_PRIMARY_EXPRESSION;
      break;
    }
    case LEXER_LEFT_BRACE:
    {
#if ENABLED (JERRY_ES2015)
      scanner_push_destructuring_pattern (context_p, scanner_context_p, SCANNER_BINDING_NONE, false);
#endif

      parser_stack_push_uint8 (context_p, SCAN_STACK_OBJECT_LITERAL);
      scanner_context_p->mode = SCAN_MODE_PROPERTY_NAME;
      return SCAN_KEEP_TOKEN;
    }
#if ENABLED (JERRY_ES2015)
    case LEXER_TEMPLATE_LITERAL:
    {
      if (context_p->source_p[-1] != LIT_CHAR_GRAVE_ACCENT)
      {
        parser_stack_push_uint8 (context_p, SCAN_STACK_TEMPLATE_STRING);
        scanner_context_p->mode = SCAN_MODE_PRIMARY_EXPRESSION;
        break;
      }


    }
#endif
    case LEXER_LITERAL:
    {
#if ENABLED (JERRY_ES2015)
      const uint8_t *source_p = context_p->source_p;

      if (context_p->token.lit_location.type == LEXER_IDENT_LITERAL
          && lexer_check_arrow (context_p))
      {
        scanner_scan_simple_arrow (context_p, scanner_context_p, source_p);
        return SCAN_KEEP_TOKEN;
      }
      else if (JERRY_UNLIKELY (lexer_token_is_async (context_p)))
      {
        scanner_context_p->async_source_p = source_p;
        scanner_check_async_function (context_p, scanner_context_p);
        return SCAN_KEEP_TOKEN;
      }
#endif

      if (context_p->token.lit_location.type == LEXER_IDENT_LITERAL)
      {
        scanner_add_reference (context_p, scanner_context_p);
      }

    }
    case LEXER_KEYW_THIS:
    case LEXER_KEYW_SUPER:
    case LEXER_LIT_TRUE:
    case LEXER_LIT_FALSE:
    case LEXER_LIT_NULL:
    {
      scanner_context_p->mode = SCAN_MODE_POST_PRIMARY_EXPRESSION;
      break;
    }
#if ENABLED (JERRY_ES2015)
    case LEXER_KEYW_CLASS:
    {
      scanner_push_class_declaration (context_p, scanner_context_p, SCAN_STACK_CLASS_EXPRESSION);

      if (context_p->token.type != LEXER_LITERAL || context_p->token.lit_location.type != LEXER_IDENT_LITERAL)
      {
        return SCAN_KEEP_TOKEN;
      }
      break;
    }
#endif
    case LEXER_RIGHT_SQUARE:
    {
      if (stack_top != SCAN_STACK_ARRAY_LITERAL)
      {
        scanner_raise_error (context_p);
      }

      scanner_context_p->mode = SCAN_MODE_PRIMARY_EXPRESSION_END;
      return SCAN_KEEP_TOKEN;
    }
#if ENABLED (JERRY_ES2015)
    case LEXER_THREE_DOTS:
    {

      if (stack_top != SCAN_STACK_PAREN_EXPRESSION && stack_top != SCAN_STACK_ARRAY_LITERAL)
      {
        scanner_raise_error (context_p);
      }
      scanner_context_p->mode = SCAN_MODE_PRIMARY_EXPRESSION;
      break;
    }
#endif
    case LEXER_COMMA:
    {
      if (stack_top != SCAN_STACK_ARRAY_LITERAL)
      {
        scanner_raise_error (context_p);
      }
      scanner_context_p->mode = SCAN_MODE_PRIMARY_EXPRESSION;

#if ENABLED (JERRY_ES2015)
      if (scanner_context_p->binding_type != SCANNER_BINDING_NONE)
      {
        scanner_context_p->mode = SCAN_MODE_BINDING;
      }
#endif
      break;
    }
#if ENABLED (JERRY_ES2015)
    case LEXER_KEYW_YIELD:
    {
      lexer_next_token (context_p);

      if (lexer_check_yield_no_arg (context_p))
      {
        scanner_context_p->mode = SCAN_MODE_PRIMARY_EXPRESSION_END;
      }

      if (context_p->token.type == LEXER_MULTIPLY)
      {
        return SCAN_NEXT_TOKEN;
      }
      return SCAN_KEEP_TOKEN;
    }
#endif
    case LEXER_RIGHT_PAREN:
    {
      if (stack_top == SCAN_STACK_PAREN_EXPRESSION)
      {
        scanner_context_p->mode = SCAN_MODE_POST_PRIMARY_EXPRESSION;
        parser_stack_pop_uint8 (context_p);
        break;
      }

    }
    default:
    {
      scanner_raise_error (context_p);
    }
  }
  return SCAN_NEXT_TOKEN;
}
