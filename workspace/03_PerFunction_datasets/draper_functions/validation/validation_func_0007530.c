db__send_string_array(dbString * a, int count)
{
    int i;
    int stat;

    stat = db__send_int(count);
    for (i = 0; stat == DB_OK && i < count; i++)
	stat = db__send_string(&a[i]);

    return stat;
}
