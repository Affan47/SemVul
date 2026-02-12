continue_command()
{
    c_token++;
    if (iteration_depth == 0)
	return;

    c_token = num_tokens;

    requested_continue = TRUE;
}
