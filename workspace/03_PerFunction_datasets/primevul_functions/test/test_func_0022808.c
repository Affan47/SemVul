uint Lex_input_stream::get_body_utf8_maximum_length(THD *thd)
{


  return (m_buf_length / thd->variables.character_set_client->mbminlen) *
          my_charset_utf8_bin.mbmaxlen * 2;
}
