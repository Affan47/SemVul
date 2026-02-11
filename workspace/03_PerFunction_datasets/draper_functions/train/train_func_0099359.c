SNSDisplay_Field ( char *p_field_name, char *p_field, int len )
{
    int indx;

    if (p_field != NULL)
    {
        __LOG_INFO ("%-19s : ", p_field_name);
        for (indx = 0; indx <  len; indx++)
            __LOG_INFO ("%2.2x", *(unsigned char *)&p_field[ indx ]);
        __LOG_INFO ("\n");
    }
}
