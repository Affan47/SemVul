CORD_range_contains_chr_greater_then_proc(char c, size_t size, void* client_data)
{
    register chr_data * d = (chr_data *)client_data;

    if (d -> countdown<=0) return(2);
    d -> countdown -= size;
    if (c > d -> target) return(1);
    return(0);
}
