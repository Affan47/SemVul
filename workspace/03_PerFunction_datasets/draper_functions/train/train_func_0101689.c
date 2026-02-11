epson1_interpret_value(struct ifd_entry *entry_ptr)
{
    int chpr = 0;

    if(entry_ptr && (PRINT_VALUE))
    {
        switch(entry_ptr->tag)
        {
            case 0x0201:
                print_startvalue();


                switch(entry_ptr->value)
                {
                    case 1: chpr += printf("SQ"); break;
                    case 2: chpr += printf("HQ"); break;
                    case 3: chpr += printf("SHQ"); break;
                    case 33: chpr += printf("not compressed"); break;
                    case 34: chpr += printf("not compressed"); break;
                    default: printred("undefined"); break;
                }
                print_endvalue();
                break;
            case 0x0202:
                print_startvalue();
                switch(entry_ptr->value)
                {
                    case 0: chpr += printf("Normal"); break;
                    case 1: chpr += printf("Macro"); break;
                    default: printred("undefined"); break;
                }
                print_endvalue();
                break;
            default:
                break;
        }
    }
    setcharsprinted(chpr);
}
