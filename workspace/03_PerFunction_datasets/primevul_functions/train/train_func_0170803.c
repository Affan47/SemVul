port resolvePort(node_t * n, node_t * other, port * oldport)
{
    port rv;
    char *compass = closestSide(n, other, oldport);


    rv.name = oldport->name;
    compassPort(n, oldport->bp, &rv, compass, oldport->side, NULL);

    return rv;
}
