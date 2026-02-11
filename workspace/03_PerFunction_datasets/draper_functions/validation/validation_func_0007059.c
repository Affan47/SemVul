namedNodeU(const StringC &str, NodePtr &ptr) const
{
  const Entity *entity
   = grove()->governingDtd()->lookupEntityTemp(0, str);

  while (!entity) {
    if (!grove()->hasDefaultEntity())
      return accessNull;


    Boolean complete = grove()->complete();
    entity = grove()->lookupDefaultedEntity(str);
    if (entity)
      break;
    if (complete)
      return accessNull;
    if (!grove()->waitForMoreNodes())
      return accessTimeout;
  }
  ptr.assign(new EntityNode(grove(), entity));
  return accessOK;
}
