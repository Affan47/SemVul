git_merge_file__normalize_inputs(
	git_merge_file_input *out,
	const git_merge_file_input *given)
{
	memcpy(out, given, sizeof(git_merge_file_input));

	if (!out->path)
		out->path = "file.txt";

	if (!out->mode)
		out->mode = 0100644;

	return out;
}
