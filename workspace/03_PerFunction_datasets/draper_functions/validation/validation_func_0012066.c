print_misc(struct bpf_insn *inst)
{
    printf("MISC ");
    switch (BPF_MISCOP(inst->code))
    {
        case BPF_TAX:
            printf("X <- A");
            break;
        case BPF_TXA:
            printf("A <- X");
            break;
        default:
            printf("???");
            break;
    }
    printf("\n");
}
