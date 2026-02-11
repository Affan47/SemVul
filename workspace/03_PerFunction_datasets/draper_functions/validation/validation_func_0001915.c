copy(dimeModel * const model) const
{
  dimeArc *a = new(model->getMemHandler()) dimeArc;
  if (!a) return NULL;

  if (!this->copyRecords(a, model)) {

    if (!model->getMemHandler()) delete a;
    a = NULL;
  }
  else {
    a->center = this->center;
    a->radius = this->radius;
    a->startAngle = this->startAngle;
    a->endAngle = this->endAngle;
    a->copyExtrusionData(this);
  }
  return a;
}
