bool Selector_List::operator==(const Expression& rhs) const
  {

    if (List_Ptr_Const ls = Cast<List>(&rhs)) { return *this == *ls; }
    if (Selector_Ptr_Const ls = Cast<Selector>(&rhs)) { return *this == *ls; }

    return false;
  }
