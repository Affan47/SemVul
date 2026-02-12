void Inspect::operator()(Boolean_Ptr b)
  {

    append_token(b->value() ? "true" : "false", b);
  }
