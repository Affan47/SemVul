generate_rand_no (int op_no)
{
        int             rand_no = 0;

        if (op_no < GF_FOP_MAXVALUE)
                rand_no = rand () % error_no_list[op_no].error_no_count;
        return rand_no;
}
