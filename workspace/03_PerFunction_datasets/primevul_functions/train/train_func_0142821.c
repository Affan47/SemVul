Complex_Selector_Obj Parser::parse_complex_selector(bool chroot)
  {

    NESTING_GUARD(nestings);
    String_Obj reference;
    lex < block_comment >();
    advanceToNextToken();
    Complex_Selector_Obj sel = SASS_MEMORY_NEW(Complex_Selector, pstate);

    if (peek < end_of_file >()) return {};


    Compound_Selector_Obj lhs;

    if (!peek_css< class_char < selector_combinator_ops > >()) {

      lhs = parse_compound_selector();
    }


    Complex_Selector::Combinator combinator = Complex_Selector::ANCESTOR_OF;
    if      (lex< exactly<'+'> >()) combinator = Complex_Selector::ADJACENT_TO;
    else if (lex< exactly<'~'> >()) combinator = Complex_Selector::PRECEDES;
    else if (lex< exactly<'>'> >()) combinator = Complex_Selector::PARENT_OF;
    else if (lex< sequence < exactly<'/'>, negate < exactly < '*' > > > >()) {

      combinator = Complex_Selector::REFERENCE;
      if (!lex < re_reference_combinator >()) return {};
      reference = SASS_MEMORY_NEW(String_Constant, pstate, lexed);
      if (!lex < exactly < '/' > >()) return {};
    }

    if (!lhs && combinator == Complex_Selector::ANCESTOR_OF) return {};


    sel->head(lhs);
    sel->combinator(combinator);
    sel->media_block(last_media_block);

    if (combinator == Complex_Selector::REFERENCE) sel->reference(reference);

    sel->has_line_break(peek_newline());


    if (!peek_css< class_char < complex_selector_delims > >()) {

      sel->tail(parse_complex_selector(true));
    }


    if (!sel->has_parent_ref() && !chroot) {

      Compound_Selector_Obj head = SASS_MEMORY_NEW(Compound_Selector, pstate);
      Parent_Selector* parent = SASS_MEMORY_NEW(Parent_Selector, pstate, false);
      parent->media_block(last_media_block);
      head->media_block(last_media_block);

      head->append(parent);

      if (!sel->head()) { sel->head(head); }

      else {
        sel = SASS_MEMORY_NEW(Complex_Selector, pstate, Complex_Selector::ANCESTOR_OF, head, sel);
        sel->media_block(last_media_block);
      }


    }

    sel->update_pstate(pstate);

    return sel;
  }
