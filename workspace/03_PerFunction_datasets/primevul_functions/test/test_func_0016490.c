void InstanceKlass::release_C_heap_structures(InstanceKlass* ik) {

  ik->release_C_heap_structures();
  ik->constants()->release_C_heap_structures();
}
