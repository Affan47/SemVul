knowledge_known(const knowledge_player *current, const char *item, const knowledge_type *kt) {
    int i;
    for (i = 0; i < current->item_count; i++) {
        if (strcmp(kt->type, current->items[i]->handler->type) == 0 && strcmp(item, current->items[i]->item) == 0) {

            return 1;
        }
    }
    return 0;
}
