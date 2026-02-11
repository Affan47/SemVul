collection_add(struct collection *col, void *element)
{
	int i;
	for(i=0; i<col->capacity; i++) {
		if(!col->list[i]) {
			col->list[i] = element;
			return;
		}
	}
	col->list = realloc(col->list, sizeof(void*) * col->capacity * 2);
	memset(&col->list[col->capacity], 0, sizeof(void *) * col->capacity);
	col->list[col->capacity] = element;
	col->capacity *= 2;
}
