initialize(XRef *xrefA, Catalog *catalog, Dict *dict) {
  Object obj1;

  if (dict->lookup("Subtype", &obj1)->isName()) {
    GooString typeName(obj1.getName());
    if (!typeName.cmp("Highlight")) {
      type = typeHighlight;
    } else if (!typeName.cmp("Underline")) {
      type = typeUnderline;
    } else if (!typeName.cmp("Squiggly")) {
      type = typeSquiggly;
    } else if (!typeName.cmp("StrikeOut")) {
      type = typeStrikeOut;
    }
  }
  obj1.free();

  if(dict->lookup("QuadPoints", &obj1)->isArray()) {
    quadrilaterals = new AnnotQuadrilaterals(obj1.getArray(), rect);
  } else {
    error(-1, "Bad Annot Text Markup QuadPoints");
    quadrilaterals = NULL;
    ok = gFalse;
  }
  obj1.free();
}
