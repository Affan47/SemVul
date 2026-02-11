insp_add_parloop (inspector_t* insp, const char* loopName, map_t* baseSetMap,
                              map_list* loopMaps)
{
  if (insp->loopCounter >= insp->nLoops)
    return INSP_MAXLOOP;


  int setSize = baseSetMap->inSetSize;
  int *indMap = baseSetMap->indMap;
  int mapSize = baseSetMap->mapSize;


  int* renumberedMap = (int*) malloc (mapSize * sizeof(int));

  if (!indMap)
  {

    mapSize = setSize;
    memcpy (renumberedMap, insp->v2rv, sizeof(int)*setSize);
  }
  else
  {

    new_codomain (indMap, mapSize, insp->v2rv, renumberedMap);
  }


  insp->loops[insp->loopCounter] = (loop_t*) malloc (sizeof(loop_t));

  insp->loops[insp->loopCounter]->loopName = (char*) malloc(sizeof(char)*LOOPNAMELENGTH);
  strncpy (insp->loops[insp->loopCounter]->loopName, loopName, LOOPNAMELENGTH);

  insp->loops[insp->loopCounter]->setSize = setSize;
  insp->loops[insp->loopCounter]->baseSetMap = renumberedMap;
  insp->loops[insp->loopCounter]->mapSize = mapSize;
  insp->loops[insp->loopCounter]->loopMaps = loopMaps;

#ifdef VTK_ON
  insp->loops[insp->loopCounter]->setColor = (int*) malloc(setSize*sizeof(int));
  insp->loops[insp->loopCounter]->coloring = 0;
#endif


  for (int i = 0; i < insp->nTiles; i++)
  {


    tile_add_parloop (insp->tiles[i], setSize, loopName);
  }

  insp->loopCounter++;
  return INSP_OK;
}
