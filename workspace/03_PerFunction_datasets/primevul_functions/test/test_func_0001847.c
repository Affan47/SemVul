bool Socket::writeString(const char *line)
{
    int l = strlen(line);
    return writeToSocket(line, l, 0, timeout);
}
