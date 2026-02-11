numhash_add_number(Numhash *table, char *nro)
{
    struct numhash_number *newnro;

    if (table->number_total == table->table_size) {
	error(0, "Table limit %ld reached, cannot add %s!",
	      table->table_size, nro);
	return -1;
    }
    newnro =  &table->numbers[table->number_total++];

    newnro->key = numhash_get_char_key(nro);
    newnro->next = NULL;

    add_item(table, newnro);

    return 0;
}
