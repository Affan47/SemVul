externalDataEntity(ExternalDataEntityEvent *event)
{
  const ExternalDataEntity *entity = event->entity();
  if (!entity)
    return;
  flushLine(dataLine);
  os() << "[&" << entity->name() << nl;
  externalEntityInfo(entity, dtdAttribute);
  os() << ']' << nl;
  delete event;
}
