process_org(astnode *org, void *arg, astnode **next)
{
    if (!xasm_args.pure_binary) {
        err(org->loc, "org directive can only be used when output format is pure 6502 binary");
    } else {
        astnode *addr = astnode_get_child(org, 0);
        addr = reduce_expression_complete(addr);
        if (astnode_is_type(addr, INTEGER_NODE)) {

            if ((addr->integer < 0) || (addr->integer >= 0x10000)) {
                err(org->loc, "org address out of 64K range");
            }
        } else {
            err(org->loc, "org address does not evaluate to literal");
            astnode_remove(org);
            astnode_finalize(org);
        }
    }
    return 0;
}
