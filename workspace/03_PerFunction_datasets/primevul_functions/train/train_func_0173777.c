bool Jsi_MapUnset(Jsi_Map *mapPtr, const void *key){
    SIGASSERT(mapPtr, MAP);
    switch (mapPtr->typ) {
        case JSI_MAP_HASH: return Jsi_HashUnset(mapPtr->v.hash, (void*)key);
        case JSI_MAP_TREE: return Jsi_TreeUnset(mapPtr->v.tree, (void*)key);
        case JSI_MAP_LIST: {


            break;
        }
        case JSI_MAP_NONE: break;
    }
    return false;
}
