getswitchvalue(char *arg, int *pj)


{
    int j,ans;

    ans = 0;
    for (j = *pj; arg[j+1] >= '0' && arg[j+1] <= '9'; ++j)
        ans = ans * 10 + (arg[j+1] - '0');

    *pj = j;
    return ans;
}
