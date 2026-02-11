method_79(const int *account, int *weight) {

    if (0 == account[0])
	return AccountNumberCheck::ERROR;
    int checkIndex = 10;

    if (2 < account[0] && 9 > account[0])
	number2Array("2121212120", weight);
    else {
	checkIndex--;
	number2Array("1212121200", weight);
    }

    return algo01(10, weight, true, checkIndex, account);
}
