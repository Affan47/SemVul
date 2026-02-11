start_raw_output_file(context *con)
{
    con->file = fopen(con->name, "w+b");
    if (con->file==0)
        error("cannot create RAW output file %s", con->name);
    con->swap = 0;
}
