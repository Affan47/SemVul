xml_element* xml_elem_new() {
   xml_element* elem = calloc(1, sizeof(xml_element));
   if(elem) {
      Q_Init(&elem->children);
      Q_Init(&elem->attrs);
      simplestring_init(&elem->text);


      simplestring_addn(&elem->text, "", 0);
   }
   return elem;
}
