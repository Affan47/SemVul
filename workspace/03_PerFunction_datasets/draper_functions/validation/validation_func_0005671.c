gcd(unsigned int a, unsigned int b)
{
    unsigned int t;

    while (b) {
        t = b;
        b = a % t;
        a = t;
    }

    return a;
}
