g_markup_parse_context_parse (GMarkupParseContext  *context,
                              const gchar          *text,
                              gssize                text_len,
                              GError              **error)
{
  g_return_val_if_fail (context != NULL, FALSE);
  g_return_val_if_fail (text != NULL, FALSE);
  g_return_val_if_fail (context->state != STATE_ERROR, FALSE);
  g_return_val_if_fail (!context->parsing, FALSE);

  if (text_len < 0)
    text_len = strlen (text);

  if (text_len == 0)
    return TRUE;

  context->parsing = TRUE;


  context->current_text = text;
  context->current_text_len = text_len;
  context->current_text_end = context->current_text + text_len;
  context->iter = context->current_text;
  context->start = context->iter;

  while (context->iter != context->current_text_end)
    {
      switch (context->state)
        {
        case STATE_START:


          g_assert (context->tag_stack == NULL);


          skip_spaces (context);

          if (context->iter != context->current_text_end)
            {
              if (*context->iter == '<')
                {

                  advance_char (context);

                  context->state = STATE_AFTER_OPEN_ANGLE;


                  context->start = context->iter;


                  context->document_empty = FALSE;
                }
              else
                {
                  set_error_literal (context,
                                     error,
                                     G_MARKUP_ERROR_PARSE,
                                     _("Document must begin with an element (e.g. <book>)"));
                }
            }
          break;

        case STATE_AFTER_OPEN_ANGLE:


          if (*context->iter == '?' ||
              *context->iter == '!')
            {

              const gchar *openangle = "<";
              add_to_partial (context, openangle, openangle + 1);
              context->start = context->iter;
              context->balance = 1;
              context->state = STATE_INSIDE_PASSTHROUGH;
            }
          else if (*context->iter == '/')
            {

              advance_char (context);

              context->state = STATE_AFTER_CLOSE_TAG_SLASH;
            }
          else if (!IS_COMMON_NAME_END_CHAR (*(context->iter)))
            {
              context->state = STATE_INSIDE_OPEN_TAG_NAME;


              context->start = context->iter;
            }
          else
            {
              gchar buf[8];

              set_error (context,
                         error,
                         G_MARKUP_ERROR_PARSE,
                         _("“%s” is not a valid character following "
                           "a “<” character; it may not begin an "
                           "element name"),
                         utf8_str (context->iter, buf));
            }
          break;


        case STATE_AFTER_CLOSE_ANGLE:

          if (context->tag_stack == NULL)
            {
              context->start = NULL;
              context->state = STATE_START;
            }
          else
            {
              context->start = context->iter;
              context->state = STATE_INSIDE_TEXT;
            }
          break;

        case STATE_AFTER_ELISION_SLASH:

          if (*context->iter == '>')
            {

              advance_char (context);
              context->state = STATE_AFTER_CLOSE_ANGLE;
              emit_end_element (context, error);
            }
          else
            {
              gchar buf[8];

              set_error (context,
                         error,
                         G_MARKUP_ERROR_PARSE,
                         _("Odd character “%s”, expected a “>” character "
                           "to end the empty-element tag “%s”"),
                         utf8_str (context->iter, buf),
                         current_element (context));
            }
          break;

        case STATE_INSIDE_OPEN_TAG_NAME:


          advance_to_name_end (context);

          if (context->iter == context->current_text_end)
            {


              add_to_partial (context, context->start, context->iter);
            }
          else
            {


              add_to_partial (context, context->start, context->iter);
              push_partial_as_tag (context);

              context->state = STATE_BETWEEN_ATTRIBUTES;
              context->start = NULL;
            }
          break;

        case STATE_INSIDE_ATTRIBUTE_NAME:


          advance_to_name_end (context);
          add_to_partial (context, context->start, context->iter);


          if (context->iter != context->current_text_end)
            context->state = STATE_AFTER_ATTRIBUTE_NAME;
          break;

        case STATE_AFTER_ATTRIBUTE_NAME:


          skip_spaces (context);

          if (context->iter != context->current_text_end)
            {


              if (!name_validate (context, context->partial_chunk->str, error))
                break;

              add_attribute (context, context->partial_chunk);

              context->partial_chunk = NULL;
              context->start = NULL;

              if (*context->iter == '=')
                {
                  advance_char (context);
                  context->state = STATE_AFTER_ATTRIBUTE_EQUALS_SIGN;
                }
              else
                {
                  gchar buf[8];

                  set_error (context,
                             error,
                             G_MARKUP_ERROR_PARSE,
                             _("Odd character “%s”, expected a “=” after "
                               "attribute name “%s” of element “%s”"),
                             utf8_str (context->iter, buf),
                             current_attribute (context),
                             current_element (context));

                }
            }
          break;

        case STATE_BETWEEN_ATTRIBUTES:


          skip_spaces (context);

          if (context->iter != context->current_text_end)
            {
              if (*context->iter == '/')
                {
                  advance_char (context);
                  context->state = STATE_AFTER_ELISION_SLASH;
                }
              else if (*context->iter == '>')
                {
                  advance_char (context);
                  context->state = STATE_AFTER_CLOSE_ANGLE;
                }
              else if (!IS_COMMON_NAME_END_CHAR (*(context->iter)))
                {
                  context->state = STATE_INSIDE_ATTRIBUTE_NAME;

                  context->start = context->iter;
                }
              else
                {
                  gchar buf[8];

                  set_error (context,
                             error,
                             G_MARKUP_ERROR_PARSE,
                             _("Odd character “%s”, expected a “>” or “/” "
                               "character to end the start tag of "
                               "element “%s”, or optionally an attribute; "
                               "perhaps you used an invalid character in "
                               "an attribute name"),
                             utf8_str (context->iter, buf),
                             current_element (context));
                }


              if (context->state == STATE_AFTER_ELISION_SLASH ||
                  context->state == STATE_AFTER_CLOSE_ANGLE)
                emit_start_element (context, error);
            }
          break;

        case STATE_AFTER_ATTRIBUTE_EQUALS_SIGN:


          skip_spaces (context);

          if (context->iter != context->current_text_end)
            {
              if (*context->iter == '"')
                {
                  advance_char (context);
                  context->state = STATE_INSIDE_ATTRIBUTE_VALUE_DQ;
                  context->start = context->iter;
                }
              else if (*context->iter == '\'')
                {
                  advance_char (context);
                  context->state = STATE_INSIDE_ATTRIBUTE_VALUE_SQ;
                  context->start = context->iter;
                }
              else
                {
                  gchar buf[8];

                  set_error (context,
                             error,
                             G_MARKUP_ERROR_PARSE,
                             _("Odd character “%s”, expected an open quote mark "
                               "after the equals sign when giving value for "
                               "attribute “%s” of element “%s”"),
                             utf8_str (context->iter, buf),
                             current_attribute (context),
                             current_element (context));
                }
            }
          break;

        case STATE_INSIDE_ATTRIBUTE_VALUE_SQ:
        case STATE_INSIDE_ATTRIBUTE_VALUE_DQ:

          {
            gchar delim;

            if (context->state == STATE_INSIDE_ATTRIBUTE_VALUE_SQ)
              {
                delim = '\'';
              }
            else
              {
                delim = '"';
              }

            do
              {
                if (*context->iter == delim)
                  break;
              }
            while (advance_char (context));
          }
          if (context->iter == context->current_text_end)
            {


              add_to_partial (context, context->start, context->iter);
            }
          else
            {
              gboolean is_ascii;


              add_to_partial (context, context->start, context->iter);

              g_assert (context->cur_attr >= 0);

              if (unescape_gstring_inplace (context, context->partial_chunk, &is_ascii, error) &&
                  (is_ascii || text_validate (context, context->partial_chunk->str,
                                              context->partial_chunk->len, error)))
                {

                  context->attr_values[context->cur_attr] = context->partial_chunk;
                  context->partial_chunk = NULL;
                  advance_char (context);
                  context->state = STATE_BETWEEN_ATTRIBUTES;
                  context->start = NULL;
                }

              truncate_partial (context);
            }
          break;

        case STATE_INSIDE_TEXT:

          do
            {
              if (*context->iter == '<')
                break;
            }
          while (advance_char (context));


          add_to_partial (context, context->start, context->iter);

          if (context->iter != context->current_text_end)
            {
              gboolean is_ascii;


              if (unescape_gstring_inplace (context, context->partial_chunk, &is_ascii, error) &&
                  (is_ascii || text_validate (context, context->partial_chunk->str,
                                              context->partial_chunk->len, error)))
                {
                  GError *tmp_error = NULL;

                  if (context->parser->text)
                    (*context->parser->text) (context,
                                              context->partial_chunk->str,
                                              context->partial_chunk->len,
                                              context->user_data,
                                              &tmp_error);

                  if (tmp_error == NULL)
                    {

                      advance_char (context);
                      context->state = STATE_AFTER_OPEN_ANGLE;

                      context->start = context->iter;
                    }
                  else
                    propagate_error (context, error, tmp_error);
                }

              truncate_partial (context);
            }
          break;

        case STATE_AFTER_CLOSE_TAG_SLASH:

          if (!IS_COMMON_NAME_END_CHAR (*(context->iter)))
            {
              context->state = STATE_INSIDE_CLOSE_TAG_NAME;


              context->start = context->iter;
            }
          else
            {
              gchar buf[8];

              set_error (context,
                         error,
                         G_MARKUP_ERROR_PARSE,
                         _("“%s” is not a valid character following "
                           "the characters “</”; “%s” may not begin an "
                           "element name"),
                         utf8_str (context->iter, buf),
                         utf8_str (context->iter, buf));
            }
          break;

        case STATE_INSIDE_CLOSE_TAG_NAME:

          advance_to_name_end (context);
          add_to_partial (context, context->start, context->iter);

          if (context->iter != context->current_text_end)
            context->state = STATE_AFTER_CLOSE_TAG_NAME;
          break;

        case STATE_AFTER_CLOSE_TAG_NAME:


          skip_spaces (context);

          if (context->iter != context->current_text_end)
            {
              GString *close_name;

              close_name = context->partial_chunk;
              context->partial_chunk = NULL;

              if (*context->iter != '>')
                {
                  gchar buf[8];

                  set_error (context,
                             error,
                             G_MARKUP_ERROR_PARSE,
                             _("“%s” is not a valid character following "
                               "the close element name “%s”; the allowed "
                               "character is “>”"),
                             utf8_str (context->iter, buf),
                             close_name->str);
                }
              else if (context->tag_stack == NULL)
                {
                  set_error (context,
                             error,
                             G_MARKUP_ERROR_PARSE,
                             _("Element “%s” was closed, no element "
                               "is currently open"),
                             close_name->str);
                }
              else if (strcmp (close_name->str, current_element (context)) != 0)
                {
                  set_error (context,
                             error,
                             G_MARKUP_ERROR_PARSE,
                             _("Element “%s” was closed, but the currently "
                               "open element is “%s”"),
                             close_name->str,
                             current_element (context));
                }
              else
                {
                  advance_char (context);
                  context->state = STATE_AFTER_CLOSE_ANGLE;
                  context->start = NULL;

                  emit_end_element (context, error);
                }
              context->partial_chunk = close_name;
              truncate_partial (context);
            }
          break;

        case STATE_INSIDE_PASSTHROUGH:

          do
            {
              if (*context->iter == '<')
                context->balance++;
              if (*context->iter == '>')
                {
                  gchar *str;
                  gsize len;

                  context->balance--;
                  add_to_partial (context, context->start, context->iter);
                  context->start = context->iter;

                  str = context->partial_chunk->str;
                  len = context->partial_chunk->len;

                  if (str[1] == '?' && str[len - 1] == '?')
                    break;
                  if (strncmp (str, "<!--", 4) == 0 &&
                      strcmp (str + len - 2, "--") == 0)
                    break;
                  if (strncmp (str, "<![CDATA[", 9) == 0 &&
                      strcmp (str + len - 2, "]]") == 0)
                    break;
                  if (strncmp (str, "<!DOCTYPE", 9) == 0 &&
                      context->balance == 0)
                    break;
                }
            }
          while (advance_char (context));

          if (context->iter == context->current_text_end)
            {


               add_to_partial (context, context->start, context->iter);
            }
          else
            {


              GError *tmp_error = NULL;

              advance_char (context);
              add_to_partial (context, context->start, context->iter);

              if (context->flags & G_MARKUP_TREAT_CDATA_AS_TEXT &&
                  strncmp (context->partial_chunk->str, "<![CDATA[", 9) == 0)
                {
                  if (context->parser->text &&
                      text_validate (context,
                                     context->partial_chunk->str + 9,
                                     context->partial_chunk->len - 12,
                                     error))
                    (*context->parser->text) (context,
                                              context->partial_chunk->str + 9,
                                              context->partial_chunk->len - 12,
                                              context->user_data,
                                              &tmp_error);
                }
              else if (context->parser->passthrough &&
                       text_validate (context,
                                      context->partial_chunk->str,
                                      context->partial_chunk->len,
                                      error))
                (*context->parser->passthrough) (context,
                                                 context->partial_chunk->str,
                                                 context->partial_chunk->len,
                                                 context->user_data,
                                                 &tmp_error);

              truncate_partial (context);

              if (tmp_error == NULL)
                {
                  context->state = STATE_AFTER_CLOSE_ANGLE;
                  context->start = context->iter;
                }
              else
                propagate_error (context, error, tmp_error);
            }
          break;

        case STATE_ERROR:
          goto finished;
          break;

        default:
          g_assert_not_reached ();
          break;
        }
    }

 finished:
  context->parsing = FALSE;

  return context->state != STATE_ERROR;
}
