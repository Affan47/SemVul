getNames(stPinchSegment *segment) {
    stSortedSet *names = stSortedSet_construct3((int(*)(const void *, const void *)) stIntTuple_cmpFn,
            (void(*)(void *)) stIntTuple_destruct);
    if (stPinchSegment_getBlock(segment) != NULL) {
        stPinchBlock *block = stPinchSegment_getBlock(segment);
        stPinchBlockIt it = stPinchBlock_getSegmentIterator(block);
        while ((segment = stPinchBlockIt_getNext(&it)) != NULL) {
            stSortedSet_insert(names, stIntTuple_construct1(stPinchSegment_getName(segment)));
        }
    } else {
        stSortedSet_insert(names, stIntTuple_construct1(stPinchSegment_getName(segment)));
    }
    return names;
}
