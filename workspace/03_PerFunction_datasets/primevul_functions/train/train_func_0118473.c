ciMethod* ciEnv::get_method_by_index_impl(const constantPoolHandle& cpool,
                                          int index, Bytecodes::Code bc,
                                          ciInstanceKlass* accessor) {
  if (bc == Bytecodes::_invokedynamic) {
    ConstantPoolCacheEntry* cpce = cpool->invokedynamic_cp_cache_entry_at(index);
    bool is_resolved = !cpce->is_f1_null();


    if (is_resolved) {


      Method* adapter = cpce->f1_as_method();
      return get_method(adapter);
    }


    ciInstanceKlass* holder    = get_instance_klass(SystemDictionary::MethodHandle_klass());
    ciSymbol*        name      = ciSymbol::invokeBasic_name();
    ciSymbol*        signature = get_symbol(cpool->signature_ref_at(index));
    return get_unloaded_method(holder, name, signature, accessor);
  } else {
    const int holder_index = cpool->klass_ref_index_at(index);
    bool holder_is_accessible;
    ciKlass* holder = get_klass_by_index_impl(cpool, holder_index, holder_is_accessible, accessor);


    Symbol* name_sym = cpool->name_ref_at(index);
    Symbol* sig_sym  = cpool->signature_ref_at(index);

    if (cpool->has_preresolution()
        || ((holder == ciEnv::MethodHandle_klass() || holder == ciEnv::VarHandle_klass()) &&
            MethodHandles::is_signature_polymorphic_name(holder->get_Klass(), name_sym))) {


      switch (bc) {
      case Bytecodes::_invokevirtual:
      case Bytecodes::_invokeinterface:
      case Bytecodes::_invokespecial:
      case Bytecodes::_invokestatic:
        {
          Method* m = ConstantPool::method_at_if_loaded(cpool, index);
          if (m != NULL) {
            return get_method(m);
          }
        }
        break;
      default:
        break;
      }
    }

    if (holder_is_accessible) {
      constantTag tag = cpool->tag_ref_at(index);
      assert(accessor->get_instanceKlass() == cpool->pool_holder(), "not the pool holder?");
      Method* m = lookup_method(accessor, holder, name_sym, sig_sym, bc, tag);
      if (m != NULL &&
          (bc == Bytecodes::_invokestatic
           ?  m->method_holder()->is_not_initialized()
           : !m->method_holder()->is_loaded())) {
        m = NULL;
      }
#ifdef ASSERT
      if (m != NULL && ReplayCompiles && !ciReplay::is_loaded(m)) {
        m = NULL;
      }
#endif
      if (m != NULL) {

        return get_method(m);
      }
    }


    ciSymbol* name      = get_symbol(name_sym);
    ciSymbol* signature = get_symbol(sig_sym);
    return get_unloaded_method(holder, name, signature, accessor);
  }
}
