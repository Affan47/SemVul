init_method_obj()
  {
    m_method_obj=RefPtr<Obj>(m_nonil_obj->clone());
    m_method_obj->def_method("a", Method(method_a, true));
    m_method_obj->def_method("e", Method(method_e, true));
  }
