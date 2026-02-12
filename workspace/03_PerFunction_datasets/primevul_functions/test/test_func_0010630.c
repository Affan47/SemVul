ciKlass* ciEnv::get_klass_by_index_impl(constantPoolHandle cpool,
                                        int index,
                                        bool& is_accessible,
                                        ciInstanceKlass* accessor) {
  EXCEPTION_CONTEXT;
  KlassHandle klass;
  Symbol* klass_name = NULL;

  if (cpool->tag_at(index).is_symbol()) {
    klass_name = cpool->symbol_at(index);
  } else {

    klass = KlassHandle(THREAD, ConstantPool::klass_at_if_loaded(cpool, index));

  if (klass.is_null()) {


    {


        MonitorLockerEx ml(cpool->lock());
      constantTag tag = cpool->tag_at(index);
      if (tag.is_klass()) {


        klass = KlassHandle(THREAD, cpool->resolved_klass_at(index));
      } else {
        assert(cpool->tag_at(index).is_unresolved_klass(), "wrong tag");
        klass_name = cpool->unresolved_klass_at(index);
      }
    }
  }
  }

  if (klass.is_null()) {

    ciKlass* k = get_klass_by_name_impl(accessor,
                                        cpool,
                                        get_symbol(klass_name),
                                        false);

    if (!k->is_loaded()) {
      is_accessible = false;
    } else if (k->loader() != accessor->loader() &&
               get_klass_by_name_impl(accessor, cpool, k->name(), true) == NULL) {

      is_accessible = false;
    } else {

      is_accessible = check_klass_accessibility(accessor, k->get_Klass());
    }
    return k;
  }


  ciSymbol* name = get_symbol(klass()->name());
  ciKlass* unloaded_klass = check_get_unloaded_klass(accessor, name);
  if (unloaded_klass != NULL) {
    is_accessible = false;
    return unloaded_klass;
  }


  is_accessible = true;
  return get_klass(klass());
}
