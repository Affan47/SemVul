getEntity(NodePtr &ptr) const
{
  if (iter_.type() != TextItem::sdata)
    return accessNotInClass;
  const Entity *entity
    = iter_.location().origin()->asEntityOrigin()->entity();
  ptr.assign(new EntityNode(grove(), entity));
  return accessOK;
}
