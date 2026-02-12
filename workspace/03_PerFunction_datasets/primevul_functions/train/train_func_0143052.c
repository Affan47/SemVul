void Inspect::operator()(Selector_List_Ptr g)
  {

    if (g->empty()) {
      if (output_style() == TO_SASS) {
        append_token("()", g);
      }
      return;
    }


    bool was_comma_array = in_comma_array;

    if (output_style() == TO_SASS && g->length() == 1 &&
      (!Cast<List>((*g)[0]) &&
       !Cast<Selector_List>((*g)[0]))) {
      append_string("(");
    }
    else if (!in_declaration && in_comma_array) {
      append_string("(");
    }

    if (in_declaration) in_comma_array = true;

    for (size_t i = 0, L = g->length(); i < L; ++i) {
      if (!in_wrapped && i == 0) append_indentation();
      if ((*g)[i] == 0) continue;
      schedule_mapping(g->at(i)->last());

      (*g)[i]->perform(this);

      if (i < L - 1) {
        scheduled_space = 0;
        append_comma_separator();
      }
    }

    in_comma_array = was_comma_array;

    if (output_style() == TO_SASS && g->length() == 1 &&
      (!Cast<List>((*g)[0]) &&
       !Cast<Selector_List>((*g)[0]))) {
      append_string(",)");
    }
    else if (!in_declaration && in_comma_array) {
      append_string(")");
    }

  }
