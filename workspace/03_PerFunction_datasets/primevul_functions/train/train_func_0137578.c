void InstanceKlass::set_nest_host(InstanceKlass* host) {
  assert(is_hidden(), "must be a hidden class");
  assert(host != NULL, "NULL nest host specified");
  assert(_nest_host == NULL, "current class has resolved nest-host");
  assert(nest_host_error() == NULL, "unexpected nest host resolution error exists: %s",
         nest_host_error());
  assert((host->_nest_host == NULL && host->_nest_host_index == 0) ||
         (host->_nest_host == host), "proposed host is not a valid nest-host");


  if (log_is_enabled(Trace, class, nestmates)) {
    ResourceMark rm;
    const char* msg = "";

    if (_nest_host_index > 0) {
      msg = "(the NestHost attribute in the current class is ignored)";
    } else if (_nest_members != NULL && _nest_members != Universe::the_empty_short_array()) {
      msg = "(the NestMembers attribute in the current class is ignored)";
    }
    log_trace(class, nestmates)("Injected type %s into the nest of %s %s",
                                this->external_name(),
                                host->external_name(),
                                msg);
  }

  _nest_host = host;

  ClassLoaderData* this_key = class_loader_data();
  this_key->record_dependency(host);
}
