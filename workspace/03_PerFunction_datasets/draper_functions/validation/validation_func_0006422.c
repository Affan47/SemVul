method_69(const int *account, int *weight) {
    int transform[6][10] =
	{ {0,0,0,0,0,0,0,0,0,0},
	  {0,1,5,9,3,7,4,8,2,6},
	  {0,1,7,6,9,8,3,2,5,4},
	  {0,1,8,4,6,2,9,5,7,3},
	  {0,1,2,3,4,5,6,7,8,9},
	  {1,4,3,2,1,4,3,2,1,0} };

    long int lastnine = atol(array2Number(account).substr(1).c_str());
    if (account[0] == 9 && lastnine >= 300000000 && lastnine <= 399999999)
	return AccountNumberCheck::OK;
    if ((account[0] == 9 && (lastnine <= 700000000 || lastnine >= 799999999)) ||
	account[0] != 9) {

	number2Array("8765432000", weight);
	if (AccountNumberCheck::OK == algo01(11, weight, false, 8, account))
	    return AccountNumberCheck::OK;
    }

    return algo07(account, transform);
}
