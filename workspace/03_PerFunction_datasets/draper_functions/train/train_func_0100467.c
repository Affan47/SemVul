purchase_analyze(s32b price, s32b value, s32b guess)
{

	if ((value <= 0) && (price > value))
		msgt(MSG_STORE1, "%s", ONE_OF(comment_worthless));


	else if ((value < guess) && (price > value))
		msgt(MSG_STORE2, "%s", ONE_OF(comment_bad));


	else if ((value > guess) && (value < (4 * guess)) && (price < value))
		msgt(MSG_STORE3, "%s", ONE_OF(comment_good));


	else if ((value > guess) && (price < value))
		msgt(MSG_STORE4, "%s", ONE_OF(comment_great));
}
