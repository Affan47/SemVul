void InstanceKlass::purge_previous_version_list() {
  assert(SafepointSynchronize::is_at_safepoint(), "only called at safepoint");
  assert(has_been_redefined(), "Should only be called for main class");


  if (previous_versions() == NULL) {
    return;
  }


  int deleted_count = 0;
  int live_count = 0;
  ClassLoaderData* loader_data = class_loader_data();
  assert(loader_data != NULL, "should never be null");

  ResourceMark rm;
  log_trace(redefine, class, iklass, purge)("%s: previous versions", external_name());


  InstanceKlass* pv_node = previous_versions();
  InstanceKlass* last = this;
  int version = 0;


  for (; pv_node != NULL; ) {

    ConstantPool* pvcp = pv_node->constants();
    assert(pvcp != NULL, "cp ref was unexpectedly cleared");

    if (!pvcp->on_stack()) {


      log_trace(redefine, class, iklass, purge)
        ("previous version " INTPTR_FORMAT " is dead.", p2i(pv_node));

      pv_node->set_is_scratch_class();

      assert(pv_node->class_loader_data() == loader_data, "wrong loader_data");
      InstanceKlass* next = pv_node->previous_versions();
      pv_node->link_previous_versions(NULL);
      last->link_previous_versions(next);

      loader_data->add_to_deallocate_list(pv_node);
      pv_node = next;
      deleted_count++;
      version++;
      continue;
    } else {
      log_trace(redefine, class, iklass, purge)("previous version " INTPTR_FORMAT " is alive", p2i(pv_node));
      assert(pvcp->pool_holder() != NULL, "Constant pool with no holder");
      guarantee (!loader_data->is_unloading(), "unloaded classes can't be on the stack");
      live_count++;

      _has_previous_versions = true;
    }


    Array<Method*>* method_refs = pv_node->methods();
    if (method_refs != NULL) {
      log_trace(redefine, class, iklass, purge)("previous methods length=%d", method_refs->length());
      for (int j = 0; j < method_refs->length(); j++) {
        Method* method = method_refs->at(j);

        if (!method->on_stack()) {

          if (method->is_running_emcp()) {
            method->set_running_emcp(false);
          }
        } else {
          assert (method->is_obsolete() || method->is_running_emcp(),
                  "emcp method cannot run after emcp bit is cleared");
          log_trace(redefine, class, iklass, purge)
            ("purge: %s(%s): prev method @%d in version @%d is alive",
             method->name()->as_C_string(), method->signature()->as_C_string(), j, version);
        }
      }
    }

    last = pv_node;
    pv_node = pv_node->previous_versions();
    version++;
  }
  log_trace(redefine, class, iklass, purge)
    ("previous version stats: live=%d, deleted=%d", live_count, deleted_count);
}
