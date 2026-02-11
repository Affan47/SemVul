output_line(Macro::parser::location_type *yylloc) const
{
  if (!no_line_macro)
    *yyout << endl << "@#line \"" << *yylloc->begin.filename << "\" "
           << yylloc->begin.line << endl;
}
