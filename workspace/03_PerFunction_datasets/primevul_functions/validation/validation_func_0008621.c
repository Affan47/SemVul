freeBindings(XML_Parser parser, BINDING *bindings)
{
  while (bindings) {
    BINDING *b = bindings;


    if (endNamespaceDeclHandler)
        endNamespaceDeclHandler(handlerArg, b->prefix->name);

    bindings = bindings->nextTagBinding;
    b->nextTagBinding = freeBindingList;
    freeBindingList = b;
    b->prefix->binding = b->prevPrefixBinding;
  }
}
