test_shift()
{
    List_shift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong last value.");

    List_shift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong last value");

    List_shift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on shift.");

    return NULL;
}
