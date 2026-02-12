bool InstanceKlass::is_override(const methodHandle& super_method, Handle targetclassloader, Symbol* targetclassname, TRAPS) {

   if (super_method->is_private()) {
     return false;
   }

   if ((super_method->is_protected()) ||
       (super_method->is_public())) {
     return true;
   }

   assert(super_method->is_package_private(), "must be package private");
   return(is_same_class_package(targetclassloader(), targetclassname));
}
