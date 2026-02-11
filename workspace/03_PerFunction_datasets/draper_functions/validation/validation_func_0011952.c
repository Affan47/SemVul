hashtable_remove(OVECTOR table, OVECTOR keysym) {
  unum h = (NUM(AT(keysym, SY_HASH)) % (table->_.length - 1)) + 1;
  OVECTOR curr, prev;

  curr = (OVECTOR) AT(table, h);
  prev = NULL;

  while (curr != NULL) {
    if ((OVECTOR) AT(curr, HASHLINK_NAME) == keysym) {
      if (prev == NULL)
	ATPUT(table, h, (OBJ) AT(curr, HASHLINK_NEXT));
      else
	ATPUT(prev, HASHLINK_NEXT, (OBJ) AT(curr, HASHLINK_NEXT));
      ATPUT(curr, HASHLINK_NEXT, NULL);

      return;
    }

    prev = curr;
    curr = (OVECTOR) AT(curr, HASHLINK_NEXT);
  }
}
