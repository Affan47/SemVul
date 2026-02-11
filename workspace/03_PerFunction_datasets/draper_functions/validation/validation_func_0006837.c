parseObject(String tag, Page *page,
			       int *currentLayer)
{
  if (tag[0] == '/')
    return 0;

  XmlAttributes attr;
  if (!parseAttributes(attr))
    return 0;

  String layer;
  if (page && currentLayer && attr.has("layer", layer)) {
    for (int i = 0; i < page->countLayers(); ++i) {
      if (page->layer(i) == layer) {
	*currentLayer = i;
	break;
      }
    }
  }

  if (tag == "group") {
    Group group(attr);
    for (;;) {
      String tag = parseToTag();
      if (tag == "/group") {
	return new Group(group);
      }
      Object *obj = parseObject(tag);
      if (!obj)
	return 0;
      group.push_back(obj);
    }
  }

  String pcdata;
  if (!attr.slash() && !parsePCDATA(tag, pcdata))
    return 0;
  String bitmapId;
  if (tag == "image" && attr.has("bitmap", bitmapId)) {
    int objNum = Lex(bitmapId).getInt();
    Bitmap bitmap;
    for (std::vector<Bitmap>::const_iterator it = iBitmaps.begin();
	 it != iBitmaps.end(); ++it) {
      if (it->objNum() == objNum) {
	bitmap = *it;
	break;
      }
    }
    assert(!bitmap.isNull());
    return ObjectFactory::createImage(tag, attr, bitmap);
  } else
    return ObjectFactory::createObject(tag, attr, pcdata);
}
