Problem_11_test(){
    string exp = "1&0^1";
    Chapter9 chapter9;
    if(chapter9.Problem_11(exp, true)!=2)
	return false;
    exp = "1&1^0|0";
    if(chapter9.Problem_11(exp, true)!=5)
	return false;
    return true;
}
