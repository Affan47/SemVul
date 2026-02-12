Klass* InstanceKlass::find_field(Symbol* name, Symbol* sig, fieldDescriptor* fd) const {


  if (find_local_field(name, sig, fd)) {
    return const_cast<InstanceKlass*>(this);
  }

  { Klass* intf = find_interface_field(name, sig, fd);
    if (intf != NULL) return intf;
  }

  { Klass* supr = super();
    if (supr != NULL) return InstanceKlass::cast(supr)->find_field(name, sig, fd);
  }

  return NULL;
}
