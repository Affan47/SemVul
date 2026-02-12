void InstanceKlass::mark_newly_obsolete_methods(Array<Method*>* old_methods,
                                                int emcp_method_count) {
  int obsolete_method_count = old_methods->length() - emcp_method_count;

  if (emcp_method_count != 0 && obsolete_method_count != 0 &&
      _previous_versions != NULL) {


    int local_count = 0;
    for (int i = 0; i < old_methods->length(); i++) {
      Method* old_method = old_methods->at(i);
      if (old_method->is_obsolete()) {

        Symbol* m_name = old_method->name();
        Symbol* m_signature = old_method->signature();


        int j = 0;
        for (InstanceKlass* prev_version = _previous_versions;
             prev_version != NULL;
             prev_version = prev_version->previous_versions(), j++) {

          Array<Method*>* method_refs = prev_version->methods();
          for (int k = 0; k < method_refs->length(); k++) {
            Method* method = method_refs->at(k);

            if (!method->is_obsolete() &&
                method->name() == m_name &&
                method->signature() == m_signature) {


              log_trace(redefine, class, iklass, add)
                ("%s(%s): flush obsolete method @%d in version @%d",
                 m_name->as_C_string(), m_signature->as_C_string(), k, j);

              method->set_is_obsolete();
              break;
            }
          }


        }

        if (++local_count >= obsolete_method_count) {

          break;
        }
      }
    }
  }
}
