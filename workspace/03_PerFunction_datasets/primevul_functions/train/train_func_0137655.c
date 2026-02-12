void InstanceKlass::release_C_heap_structures() {


  release_C_heap_structures_internal();
  constants()->release_C_heap_structures();


  methods_do(method_release_C_heap_structures);
}
