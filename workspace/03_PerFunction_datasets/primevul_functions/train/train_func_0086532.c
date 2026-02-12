static Object HHVM_METHOD(SimpleXMLElement, attributes,
                          const String& ns ,
                          bool is_prefix ) {
  auto data = Native::data<SimpleXMLElement>(this_);
  if (data->iter.type == SXE_ITER_ATTRLIST) {
    return Object();
  }

  xmlNodePtr node = data->nodep();
  node = php_sxe_get_first_node(data, node);
  return _node_as_zval(data, node, SXE_ITER_ATTRLIST, nullptr,
                       (xmlChar*)ns.data(), is_prefix);
}
