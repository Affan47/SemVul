assert_branch_list_contains(git_strarray *branches, const char* expected_branch_name)
{
	unsigned int i;

	for (i = 0; i < branches->count; i++) {
		if (strcmp(expected_branch_name, branches->strings[i]) == 0)
			return;
	}

	cl_fail("expected branch not found in list.");
}
