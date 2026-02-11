ReadUVCoordinates (CObject *object, Chunk *previousChunk)
{
  previousChunk->bytesRead += file->readUInt16 ((Uint16 *) &object->numTexVertex);

  CVector2 *p = new CVector2 [object->numTexVertex];
  if (p == NULL) error_outofmemory ();

  previousChunk->bytesRead += file->readFloat ((float *) p, (previousChunk->length - previousChunk->bytesRead) / 4);

  for (int i = 0; i < object->numTexVertex; i ++)
    object->vertex [i].tex.take (&p [i]);
  delete p;
}
