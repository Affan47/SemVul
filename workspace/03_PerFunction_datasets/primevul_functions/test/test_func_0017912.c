void LinkResolver::resolve_invokedynamic(CallInfo& result, const constantPoolHandle& pool, int indy_index, TRAPS) {
  ConstantPoolCacheEntry* cpce = pool->invokedynamic_cp_cache_entry_at(indy_index);
  int pool_index = cpce->constant_pool_index();


  BootstrapInfo bootstrap_specifier(pool, pool_index, indy_index);


  {
    bool is_done = bootstrap_specifier.resolve_previously_linked_invokedynamic(result, CHECK);
    if (is_done) return;
  }


  resolve_dynamic_call(result, bootstrap_specifier, CHECK);

  LogTarget(Debug, methodhandles, indy) lt_indy;
  if (lt_indy.is_enabled()) {
    LogStream ls(lt_indy);
    bootstrap_specifier.print_msg_on(&ls, "resolve_invokedynamic");
  }


  ArchiveUtils::log_to_classlist(&bootstrap_specifier, CHECK);
}
