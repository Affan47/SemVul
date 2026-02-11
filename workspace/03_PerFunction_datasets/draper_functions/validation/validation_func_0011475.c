test_set_from_string() {
    big_int a = bi_init("500");
    if (a.number[3] == EON && a.number[2] ==5 && a.number[1] == 0 && a.number[0] == 0) {
        return 1;
    }
    printf("\nUnexpected Values: %d, %d, %d, %d\n", a.number[3], a.number[2], a.number[1], a.number[0]);
    return 0;
}
