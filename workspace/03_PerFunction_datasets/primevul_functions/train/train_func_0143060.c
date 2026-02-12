void Inspect::operator()(Arguments_Ptr a)
  {
    append_string("(");
    if (!a->empty()) {
      (*a)[0]->perform(this);
      for (size_t i = 1, L = a->length(); i < L; ++i) {
        append_string(", ");

        (*a)[i]->perform(this);
      }
    }
    append_string(")");
  }
