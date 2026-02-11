sh_number_of_writes_needed (unsigned char *write_needed, int child_count)
{
        int writes = 0;
        int i      = 0;

        for (i = 0; i < child_count; i++) {
                if (write_needed[i])
                        writes++;
        }

        return writes;
}
