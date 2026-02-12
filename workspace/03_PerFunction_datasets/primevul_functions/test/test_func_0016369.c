JNIid* InstanceKlass::jni_id_for_impl(int offset) {
  MutexLocker ml(JfieldIdCreation_lock);

  JNIid* probe = jni_ids() == NULL ? NULL : jni_ids()->find(offset);
  if (probe == NULL) {

    probe = new JNIid(this, offset, jni_ids());
    set_jni_ids(probe);
  }
  return probe;
}
