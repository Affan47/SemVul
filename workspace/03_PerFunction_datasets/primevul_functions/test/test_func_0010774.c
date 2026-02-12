init_string(void)

{
    if (my_string == 0)
	TYPE_MALLOC(char, my_length = 256, my_string);

    *my_string = '\0';
    return my_string;
}
