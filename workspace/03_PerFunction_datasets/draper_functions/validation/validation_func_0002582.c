recvfrom_blocking(void *data)
{
    struct recvfrom_arg *arg = data;
    return (VALUE)recvfrom(arg->fd, RSTRING_PTR(arg->str), RSTRING_LEN(arg->str),
			   arg->flags, (struct sockaddr*)&arg->buf, &arg->alen);
}
