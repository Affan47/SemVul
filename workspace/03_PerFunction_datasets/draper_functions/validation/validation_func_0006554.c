register_child(pid_t pid)
{
    unsigned long i = find_pid(0);
    if (i != (unsigned long)-1)
	childtab[i] = pid;
    ++num_children;
    ++total_forks;
}
