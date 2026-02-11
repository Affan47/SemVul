array2Number(const int a[10]) {
    string result("0000000000");
    for (unsigned i=0; i<10; i++) {
	result[i] = '0' + a[i];
    }

    return result;
}
