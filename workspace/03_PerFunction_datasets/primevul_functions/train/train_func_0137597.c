InstanceKlass* InstanceKlass::implementor() const {
  InstanceKlass* volatile* ik = adr_implementor();
  if (ik == NULL) {
    return NULL;
  } else {

    InstanceKlass* ikls = Atomic::load_acquire(ik);
    if (ikls != NULL && !ikls->is_loader_alive()) {
      return NULL;
    } else {
      return ikls;
    }
  }
}
