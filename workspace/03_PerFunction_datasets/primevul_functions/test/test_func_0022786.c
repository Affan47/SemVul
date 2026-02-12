void Lex_input_stream::body_utf8_append_escape(THD *thd,
                                               const LEX_STRING *txt,
                                               CHARSET_INFO *cs,
                                               const char *end_ptr,
                                               my_wc_t sep)
{
  DBUG_ASSERT(sep == '\'' || sep == '"');
  if (!m_cpp_utf8_processed_ptr)
    return;
  uint errors;


  DBUG_ASSERT(m_body_utf8 + get_body_utf8_maximum_length(thd) >=
              m_body_utf8_ptr + txt->length * 2);
  uint32 cnv_length= my_convert_using_func(m_body_utf8_ptr, txt->length * 2,
                                           &my_charset_utf8_general_ci,
                                           get_escape_func(thd, sep),
                                           txt->str, txt->length,
                                           cs, cs->cset->mb_wc,
                                           &errors);
  m_body_utf8_ptr+= cnv_length;
  *m_body_utf8_ptr= 0;
  m_cpp_utf8_processed_ptr= end_ptr;
}
