generateFieldAppearance() {
  Object appearDict, obj1, obj2;
  GfxResources *resources;
  MemStream *appearStream;
  GooString *da;

  appearBuf = new GooString ();


  if (appearCharacs) {
    AnnotColor *aColor = appearCharacs->getBackColor();
    if (aColor) {
      setColor(aColor, gTrue);
      appearBuf->appendf("0 0 {0:.2f} {1:.2f} re f\n",
                         rect->x2 - rect->x1, rect->y2 - rect->y1);
    }
  }


  if (appearCharacs && border && border->getWidth() > 0)
    drawBorder();

  da = field->getDefaultAppearance();
  if (!da)
    da = form->getDefaultAppearance();

  resources = form->getDefaultResources();


  switch (field->getType()) {
  case formButton:
    drawFormFieldButton(resources, da);
    break;
  case formText:
    drawFormFieldText(resources, da);
    break;
  case formChoice:
    drawFormFieldChoice(resources, da);
    break;
  case formSignature:

    break;
  case formUndef:
  default:
    error(errSyntaxError, -1, "Unknown field type");
  }


  appearDict.initDict(xref);
  appearDict.dictAdd(copyString("Length"),
      obj1.initInt(appearBuf->getLength()));
  appearDict.dictAdd(copyString("Subtype"), obj1.initName("Form"));
  obj1.initArray(xref);
  obj1.arrayAdd(obj2.initReal(0));
  obj1.arrayAdd(obj2.initReal(0));
  obj1.arrayAdd(obj2.initReal(rect->x2 - rect->x1));
  obj1.arrayAdd(obj2.initReal(rect->y2 - rect->y1));
  appearDict.dictAdd(copyString("BBox"), &obj1);


  Object *resDict = form->getDefaultResourcesObj();
  if (resDict->isDict()) {
    appearDict.dictAdd(copyString("Resources"), resDict->copy(&obj1));
  }


  appearStream = new MemStream(copyString(appearBuf->getCString()), 0,
      appearBuf->getLength(), &appearDict);
  appearance.free();
  appearance.initStream(appearStream);
  delete appearBuf;

  appearStream->setNeedFree(gTrue);
}
