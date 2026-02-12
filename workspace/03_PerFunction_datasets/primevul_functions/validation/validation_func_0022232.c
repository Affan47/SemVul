read_line(const char *prompt, int start)
{
    int more;
    char expand_prompt[40];

    current_prompt = prompt;

    prompt_desc.dsc$w_length = strlen(prompt);
    prompt_desc.dsc$a_pointer = (char *) prompt;
    strcpy(expand_prompt, "_");
    strncat(expand_prompt, prompt, sizeof(expand_prompt) - 2);
    do {
	line_desc.dsc$w_length = MAX_LINE_LEN - start;
	line_desc.dsc$a_pointer = &gp_input_line[start];
	switch (status[1] = smg$read_composed_line(&vms_vkid, &vms_ktid, &line_desc, &prompt_desc, &vms_len)) {
	case SMG$_EOF:
	    done(EXIT_SUCCESS);
	    break;
	case RMS$_TNS:
	    vms_len--;
	    break;
	case RMS$_BES:
	case RMS$_PES:
	    sys$putmsg(status);
	    vms_len = 0;
	    break;
	case SS$_NORMAL:
	    break;
	default:
	    done(status[1]);
	}
	start += vms_len;
	gp_input_line[start] = NUL;
	inline_num++;
	if (gp_input_line[start - 1] == '\\') {

	    prompt_desc.dsc$w_length = strlen(expand_prompt);
	    prompt_desc.dsc$a_pointer = expand_prompt;
	    more = 1;
	    --start;
	} else {
	    line_desc.dsc$w_length = strlen(gp_input_line);
	    line_desc.dsc$a_pointer = gp_input_line;
	    more = 0;
	}
    } while (more);
    return 0;
}
