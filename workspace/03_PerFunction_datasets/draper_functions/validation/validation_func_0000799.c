copy(dimeModel * const model) const
{
  dimeLWPolyline *l = new(model->getMemHandler()) dimeLWPolyline;
  if (!l) return NULL;

  dimeMemHandler *mh = model->getMemHandler();

  if (!this->copyRecords(l, model)) {

    if (!mh) delete l;
    l = NULL;
  }
  else {
    const int num = this->numVertices;
    if (num > 0) {
      l->xcoord = ARRAY_NEW(mh, dxfdouble, num);
      l->ycoord = ARRAY_NEW(mh, dxfdouble, num);
      l->bulge = ARRAY_NEW(mh, dxfdouble, num);
      if (this->startingWidth) {
	l->startingWidth = ARRAY_NEW(mh, dxfdouble, num);
	l->endWidth = ARRAY_NEW(mh, dxfdouble, num);
      }
      for (int i = 0; i < num; i++) {
	l->xcoord[i] = this->xcoord[i];
	l->ycoord[i] = this->ycoord[i];
	l->bulge[i] = this->bulge[i];
	if (this->startingWidth) {
	  l->startingWidth[i] = this->startingWidth[i];
	  l->endWidth[i] = this->endWidth[i];
	}
      }
    }
    l->flags = this->flags;
    l->numVertices = this->numVertices;
    l->constantWidth = this->constantWidth;
    l->elevation = this->elevation;
    l->copyExtrusionData(this);
  }
  return l;
}
