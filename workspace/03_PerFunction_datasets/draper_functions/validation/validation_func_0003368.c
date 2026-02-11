attachDateStaticInterface(as_object& o)
{
    VM& vm = getVM(o);
    const int flags = as_object::DefaultFlags | PropFlags::readOnly;
    o.init_member("UTC", vm.getNative(103, 257), flags);
}
