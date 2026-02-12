bool is_probably_prime(const UnsignedBigInteger& p)
{

    if (p < 49) {
        u32 p_value = p.words()[0];

        if (p_value == 2 || p_value == 3 || p_value == 5 || p_value == 7)
            return true;

        if (p_value % 2 == 0 || p_value % 3 == 0 || p_value % 5 == 0 || p_value % 7 == 0)
            return false;

        return true;
    }

    Vector<UnsignedBigInteger, 256> tests;

    tests.append(UnsignedBigInteger(2));
    tests.append(UnsignedBigInteger(3));
    tests.append(UnsignedBigInteger(5));
    tests.append(UnsignedBigInteger(7));
    tests.append(UnsignedBigInteger(11));
    tests.append(UnsignedBigInteger(13));
    UnsignedBigInteger seventeen { 17 };
    for (size_t i = tests.size(); i < 256; ++i) {
        tests.append(random_number(seventeen, p.minus(2)));
    }


    return MR_primality_test(p, tests);
}
