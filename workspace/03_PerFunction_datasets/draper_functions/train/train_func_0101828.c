xml_text(GMarkupParseContext *context,
         const gchar         *text,
         gsize                text_len,
         gpointer             user_data,
         GError             **error)
{
  WorldParser *parser = (WorldParser *)user_data;
  gchar       *tmp;

  if (parser->forWorldSelector
      && parser->state != KC_NAME
      && parser->state != KC_CHARACTER
      && parser->state != KC_PASSWORD) {
    return;
  }

  switch (parser->state) {
  case KC_NAME:
  case KC_HOST:
  case KC_PORT:
  case KC_CHARSET:
  case KC_TERMINALFONT:
  case KC_ENTRYFONT:
  case KC_STATUSFONT:
  case KC_FLOOD_PREVENTION:
  case KC_LOGFILE:
  case KC_LOGTIMEFORMAT:
  case KC_SCRIPTFILE:
  case KC_PLUGIN:
  case KC_PATTERN:
  case KC_ACTION:
  case KC_SUBSTITUTION:
  case KC_TIMER:
  case KC_VARIABLE:
  case KC_HOOKV1:
  case KC_HOOKV2:
    copy_text(parser->currText, text, text_len);
    break;

  case KC_CHARACTER:


    if (parser->world->logon_characters) {
      copy_text(&tmp, text, text_len);
      gtk_list_store_append(GTK_LIST_STORE(parser->world->logon_characters),
                            &parser->curr_logon_iter);
      gtk_list_store_set(GTK_LIST_STORE(parser->world->logon_characters),
                         &parser->curr_logon_iter,
                         LOGON_CHAR, tmp,
                         -1);
      g_free(tmp);
    }
    break;

  case KC_PASSWORD:
    if (parser->world->logon_characters) {
      copy_text(&tmp, text, text_len);
      gtk_list_store_set(GTK_LIST_STORE(parser->world->logon_characters),
                         &parser->curr_logon_iter,
                         LOGON_PASS, tmp,
                         -1);
      g_free(tmp);
    }
    break;

  case KC_USEBOLD:
    parser->world->usebold = text[0] - '0';
    break;

  case KC_DEFFORECOLOR:
  case KC_DEFBACKCOLOR:
  case KC_DEFBOLDCOLOR:
  case KC_DEFBOLDBACKCOLOR:
  case KC_ANSICOLOR:
    read_color(parser->currColor, text, text_len, error);
    break;

  case KC_KEY: {
    guint            keyval;
    GdkModifierType  modifiers;
    gchar           *key;

    copy_text(&key, text, text_len);
    gtk_accelerator_parse(key, &keyval, &modifiers);
    if (keyval) {
      parser->currMacro->keyval    = keyval;
      parser->currMacro->modifiers = modifiers;
    } else {
      g_set_error(error,
                  G_MARKUP_ERROR, G_MARKUP_ERROR_INVALID_CONTENT,
                  _("Invalid key code '%s'"),
                  key);
    }
    g_free(key);
    break;
  }

  default:

    break;
  }
}
