void InstanceKlass::notify_unload_class(InstanceKlass* ik) {

  if (JvmtiExport::should_post_class_unload()) {
    JvmtiExport::post_class_unload(ik);
  }


  ClassLoadingService::notify_class_unloaded(ik);
}
