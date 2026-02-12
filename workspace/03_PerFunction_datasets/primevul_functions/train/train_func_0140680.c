static int ceil_log_2(int val)
{
    int result;


    if (val == 1) {
        return 0;
    }

    result = 1;
    val -= 1;
    while (val >>= 1) {
        result++;
    }

    return result;
}
