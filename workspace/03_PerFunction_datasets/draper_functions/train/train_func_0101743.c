atoms_copy(int argc, t_atom *from, t_atom *to)
{
    int i;
    for (i = 0; i < argc; i++)
        to[i] = from[i];
}
