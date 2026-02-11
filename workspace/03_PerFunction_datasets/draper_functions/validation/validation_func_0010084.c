insert(int line, FL_BLINE* item) {
  if (!first) {
    item->prev = item->next = 0;
    first = last = item;
  } else if (line <= 1) {
    inserting(first, item);
    item->prev = 0;
    item->next = first;
    item->next->prev = item;
    first = item;
  } else if (line > lines) {
    item->prev = last;
    item->prev->next = item;
    item->next = 0;
    last = item;
  } else {
    FL_BLINE* n = find_line(line);
    inserting(n, item);
    item->next = n;
    item->prev = n->prev;
    item->prev->next = item;
    n->prev = item;
  }
  cacheline = line;
  cache = item;
  lines++;
  full_height_ += item_height(item);
  redraw_line(item);
}
