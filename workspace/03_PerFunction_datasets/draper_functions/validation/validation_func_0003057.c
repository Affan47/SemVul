new_op(u8 op_code, u8 atom_op_type, struct expr *op_arg)
{
    struct atom *atom;

    atom = chunkpool_malloc(s_atom_pool);
    atom->type = atom_op_type;
    atom->u.op.code = op_code;
    atom->u.op.arg = op_arg;

    switch(atom_op_type)
    {
    case ATOM_TYPE_OP_ARG_NONE:
        pc_add(1);
        break;
    case ATOM_TYPE_OP_ARG_U8:
        pc_add(2);
        break;
    case ATOM_TYPE_OP_ARG_U16:
        pc_add(3);
        break;
    case ATOM_TYPE_OP_ARG_I8:
        pc_add(2);
        atom->u.op.arg = new_expr_op2(MINUS, atom->u.op.arg, pc_get());
        break;
    case ATOM_TYPE_OP_ARG_UI8:
        pc_add(2);
        break;
    default:
        LOG(LOG_ERROR, ("invalid op arg range %d\n", atom_op_type));
        exit(1);
    }
    pc_dump(LOG_DEBUG);

    return atom;
}
