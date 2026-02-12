ciKlass* ciEnv::get_klass_by_name_impl(ciKlass* accessing_klass,
                                       const constantPoolHandle& cpool,
                                       ciSymbol* name,
                                       bool require_local) {
  ASSERT_IN_VM;
  Thread* current = Thread::current();


  Symbol* sym = name->get_symbol();
  if (Signature::has_envelope(sym)) {


    TempNewSymbol strippedsym = Signature::strip_envelope(sym);
    ciSymbol* strippedname = get_symbol(strippedsym);
    return get_klass_by_name_impl(accessing_klass, cpool, strippedname, require_local);
  }


  ciKlass* unloaded_klass = check_get_unloaded_klass(accessing_klass, name);
  if (unloaded_klass != NULL) {
    if (require_local)  return NULL;
    return unloaded_klass;
  }

  Handle loader;
  Handle domain;
  if (accessing_klass != NULL) {
    loader = Handle(current, accessing_klass->loader());
    domain = Handle(current, accessing_klass->protection_domain());
  }

  Klass* found_klass;
  {
    ttyUnlocker ttyul;
    MutexLocker ml(current, Compile_lock);
    Klass* kls;
    if (!require_local) {
      kls = SystemDictionary::find_constrained_instance_or_array_klass(current, sym, loader);
    } else {
      kls = SystemDictionary::find_instance_or_array_klass(sym, loader, domain);
    }
    found_klass = kls;
  }


  if (Signature::is_array(sym) &&
      (sym->char_at(1) == JVM_SIGNATURE_ARRAY || sym->char_at(1) == JVM_SIGNATURE_CLASS)) {


    SignatureStream ss(sym, false);
    ss.skip_array_prefix(1);

    ciKlass* elem_klass =
      get_klass_by_name_impl(accessing_klass,
                             cpool,
                             get_symbol(ss.as_symbol()),
                             require_local);
    if (elem_klass != NULL && elem_klass->is_loaded()) {

      return ciObjArrayKlass::make_impl(elem_klass);
    }
  }

  if (found_klass == NULL && !cpool.is_null() && cpool->has_preresolution()) {

    for (int i = cpool->length() - 1; i >= 1; i--) {
      if (cpool->tag_at(i).is_klass()) {
        Klass* kls = cpool->resolved_klass_at(i);
        if (kls->name() == sym) {
          found_klass = kls;
          break;
        }
      }
    }
  }

  if (found_klass != NULL) {

    return get_klass(found_klass);
  }

  if (require_local)  return NULL;


  return get_unloaded_klass(accessing_klass, name);
}
