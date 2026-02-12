LinkInfo::LinkInfo(const constantPoolHandle& pool, int index, TRAPS) {

  _resolved_klass = pool->klass_ref_at(index, CHECK);


  _name          = pool->name_ref_at(index);
  _signature     = pool->signature_ref_at(index);
  _tag           = pool->tag_ref_at(index);
  _current_klass = pool->pool_holder();
  _current_method = methodHandle();


  _check_access  = true;
}
