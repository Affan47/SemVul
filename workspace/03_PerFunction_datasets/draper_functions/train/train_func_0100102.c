getParentEmfObject()
{
  ModelObject* obj = model->getModelObjectById(parentId);

  if ( obj == NULL ) return NULL;

  BodyElementGroup* beg = (BodyElementGroup*)obj;


  if ( IMPLICIT_GROUP == beg->getGroupType() ) {
    int be_id = beg->getElementId(0);
    obj = model->getModelObjectById(be_id);
  }

  return obj;
}
