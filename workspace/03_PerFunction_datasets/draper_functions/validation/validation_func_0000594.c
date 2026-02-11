pattern_list_pop_heap_once(struct matched_patterns_list_data *list)
{
  int parent;
  int child;

  list->heap_num_patterns--;
  for (parent = 0; 2 * parent + 1 < list->heap_num_patterns; parent = child) {
    child = 2 * parent + 1;
    if (BETTER_PATTERN(list->pattern_heap[child + 1],
		       list->pattern_heap[child]))
      child++;

    if (BETTER_PATTERN(list->pattern_heap[list->heap_num_patterns],
		       list->pattern_heap[child]))
      break;

    list->pattern_heap[parent] = list->pattern_heap[child];
  }

  list->pattern_heap[parent] = list->pattern_heap[list->heap_num_patterns];
}
