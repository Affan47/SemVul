static bool skip_this_pass(int severity)
{


    if ((severity & ERR_MASK) > ERR_NONFATAL)
	return false;


    return (((severity & ERR_PASS1) && passn != 1) ||
	    ((severity & ERR_PASS2) && pass0 != 2));
}
