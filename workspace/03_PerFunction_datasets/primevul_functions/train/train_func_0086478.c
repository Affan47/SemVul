static Array HHVM_METHOD(SimpleXMLElement, getDocNamespaces,
                         bool recursive ,
                         bool from_root ) {
  auto data = Native::data<SimpleXMLElement>(this_);
  xmlNodePtr node =
    from_root ? xmlDocGetRootElement(data->docp())
              : data->nodep();
  Array ret = Array::Create();
  sxe_add_registered_namespaces(data, node, recursive, ret);
  return ret;
}
