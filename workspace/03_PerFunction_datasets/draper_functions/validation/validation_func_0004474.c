Fread(void *ptr, int size, int nitems, dlb *stream)
{
    int cnt;

    if ((cnt = dlb_fread(ptr, size, nitems, stream)) != nitems)
    {

        panic("PREMATURE EOF ON QUEST TEXT FILE! Expected %d bytes, got %d",
              (size * nitems), (size * cnt));
    }
}
