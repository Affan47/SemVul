method_07(const int *account, int *weight) {
    number2Array("0987654320", weight);
    weight[0] = 10;
    return algo02(11, weight, 10, account, 0, 8);
}
