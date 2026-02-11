gucharmap_get_unicode_category_name (gunichar wc)
{
  _gucharmap_intl_ensure_initialized ();

  switch (gucharmap_unichar_type (wc))
    {
      case G_UNICODE_CONTROL: return _("Other, Control");
      case G_UNICODE_FORMAT: return _("Other, Format");
      case G_UNICODE_UNASSIGNED: return _("Other, Not Assigned");
      case G_UNICODE_PRIVATE_USE: return _("Other, Private Use");
      case G_UNICODE_SURROGATE: return _("Other, Surrogate");
      case G_UNICODE_LOWERCASE_LETTER: return _("Letter, Lowercase");
      case G_UNICODE_MODIFIER_LETTER: return _("Letter, Modifier");
      case G_UNICODE_OTHER_LETTER: return _("Letter, Other");
      case G_UNICODE_TITLECASE_LETTER: return _("Letter, Titlecase");
      case G_UNICODE_UPPERCASE_LETTER: return _("Letter, Uppercase");
      case G_UNICODE_COMBINING_MARK: return _("Mark, Spacing Combining");
      case G_UNICODE_ENCLOSING_MARK: return _("Mark, Enclosing");
      case G_UNICODE_NON_SPACING_MARK: return _("Mark, Non-Spacing");
      case G_UNICODE_DECIMAL_NUMBER: return _("Number, Decimal Digit");
      case G_UNICODE_LETTER_NUMBER: return _("Number, Letter");
      case G_UNICODE_OTHER_NUMBER: return _("Number, Other");
      case G_UNICODE_CONNECT_PUNCTUATION: return _("Punctuation, Connector");
      case G_UNICODE_DASH_PUNCTUATION: return _("Punctuation, Dash");
      case G_UNICODE_CLOSE_PUNCTUATION: return _("Punctuation, Close");
      case G_UNICODE_FINAL_PUNCTUATION: return _("Punctuation, Final Quote");
      case G_UNICODE_INITIAL_PUNCTUATION: return _("Punctuation, Initial Quote");
      case G_UNICODE_OTHER_PUNCTUATION: return _("Punctuation, Other");
      case G_UNICODE_OPEN_PUNCTUATION: return _("Punctuation, Open");
      case G_UNICODE_CURRENCY_SYMBOL: return _("Symbol, Currency");
      case G_UNICODE_MODIFIER_SYMBOL: return _("Symbol, Modifier");
      case G_UNICODE_MATH_SYMBOL: return _("Symbol, Math");
      case G_UNICODE_OTHER_SYMBOL: return _("Symbol, Other");
      case G_UNICODE_LINE_SEPARATOR: return _("Separator, Line");
      case G_UNICODE_PARAGRAPH_SEPARATOR: return _("Separator, Paragraph");
      case G_UNICODE_SPACE_SEPARATOR: return _("Separator, Space");
      default: return "";
    }
}
