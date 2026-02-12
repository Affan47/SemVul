level_cost(unsigned int n)
{
    static const double log_1_1 = 0.09531017980432493;


	return ceil(log(n + 0.1)/log_1_1);
}
