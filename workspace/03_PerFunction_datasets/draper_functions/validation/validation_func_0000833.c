validate_class(node *tree)
{
    int nch = NCH(tree);
    int res = (validate_ntype(tree, classdef) &&
                ((nch == 4) || (nch == 6) || (nch == 7)));

    if (res) {
        res = (validate_name(CHILD(tree, 0), "class")
               && validate_ntype(CHILD(tree, 1), NAME)
               && validate_colon(CHILD(tree, nch - 2))
               && validate_suite(CHILD(tree, nch - 1)));
    }
    else {
        (void) validate_numnodes(tree, 4, "class");
    }

    if (res) {
        if (nch == 7) {
                res = ((validate_lparen(CHILD(tree, 2)) &&
                        validate_arglist(CHILD(tree, 3)) &&
                        validate_rparen(CHILD(tree, 4))));
        }
        else if (nch == 6) {
                res = (validate_lparen(CHILD(tree,2)) &&
                        validate_rparen(CHILD(tree,3)));
        }
    }
    return (res);
}
