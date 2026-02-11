peekCodeUnit(collIterate *source, int32_t offset) {
    if(source->pos != NULL) {
        return *(source->pos + offset);
    } else if(source->iterator != NULL) {
        UChar32 c;
        if(offset != 0) {
            source->iterator->move(source->iterator, offset, UITER_CURRENT);
            c = source->iterator->next(source->iterator);
            source->iterator->move(source->iterator, -offset-1, UITER_CURRENT);
        } else {
            c = source->iterator->current(source->iterator);
        }
        return c >= 0 ? (UChar)c : 0xfffd;
    } else {
        return 0xfffd;
    }
}
