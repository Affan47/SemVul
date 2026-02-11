countlines(char *buffer)
{
    int ans;
    const char *p;

    p = buffer - 1;
    ans = 1;
    while (p) {
	p = strchr(p + 1, '\n');
	ans++;
    }
    return ans;
}
