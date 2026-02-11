get_charcode(VMG_ uint argc)
{
    const char *str;


    check_argc(vmg_ argc, 1);


    str = pop_str_val(vmg0_);


    if (vmb_get_len(str) == 0)
    {

        retval_nil(vmg0_);
    }
    else
    {


        retval_int(vmg_ (int)utf8_ptr::s_getch(str + VMB_LEN));
    }
}
