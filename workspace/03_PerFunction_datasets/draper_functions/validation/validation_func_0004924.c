test_object_raw_convert__convert_oid_partially(void)
{
	const char *exp = "16a0123456789abcdef4b775213c23a8bd74f5e0";
	git_oid in;
	char big[GIT_OID_HEXSZ + 1 + 3];

	cl_git_pass(git_oid_fromstr(&in, exp));

	git_oid_nfmt(big, sizeof(big), &in);
	cl_assert_equal_s(exp, big);

	git_oid_nfmt(big, GIT_OID_HEXSZ + 1, &in);
	cl_assert_equal_s(exp, big);

	check_partial_oid(big, 1, &in, "1");
	check_partial_oid(big, 2, &in, "16");
	check_partial_oid(big, 3, &in, "16a");
	check_partial_oid(big, 4, &in, "16a0");
	check_partial_oid(big, 5, &in, "16a01");

	check_partial_oid(big, GIT_OID_HEXSZ, &in, exp);
	check_partial_oid(
		big, GIT_OID_HEXSZ - 1, &in, "16a0123456789abcdef4b775213c23a8bd74f5e");
	check_partial_oid(
		big, GIT_OID_HEXSZ - 2, &in, "16a0123456789abcdef4b775213c23a8bd74f5");
	check_partial_oid(
		big, GIT_OID_HEXSZ - 3, &in, "16a0123456789abcdef4b775213c23a8bd74f");
}
