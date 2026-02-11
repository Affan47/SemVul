method_51_exception(const int *account, int *weight) {
	number2Array("0087654320", weight);
	if (AccountNumberCheck::OK == algo01(11, weight, false, 10, account))
	    return AccountNumberCheck::OK;
	number2Array("0987654320", weight); weight[0] = 10;
	return algo01(11, weight, false, 10, account);
}
