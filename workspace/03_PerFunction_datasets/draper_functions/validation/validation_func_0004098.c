hashNext(int head, const int offset)
{
    head -= offset;
    if(head < 0)
        head += LZW_HASH_SIZE;
    return head;
}
