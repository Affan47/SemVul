dump_stack(struct parse_state *s, FILE *output)
{
    fprintf(output, "Stack dump:\n");
    struct grammar *g = s->bound_grammar->grammar;
    for(int i = 0; i < s->parse_stack_len; i++)
    {
        struct parse_stack_frame *frame = &s->parse_stack[i];
        switch(frame->frame_type)
        {
            case FRAME_TYPE_RTN:
            {
                struct rtn_frame *rtn_frame = &frame->f.rtn_frame;
                fprintf(output, "RTN: %s", rtn_frame->rtn->name);
                break;
            }

            case FRAME_TYPE_GLA:
            {
                struct gla_frame *gla_frame = &frame->f.gla_frame;
                fprintf(output, "GLA: #%d", gla_frame->gla - g->glas);
                break;
            }

            case FRAME_TYPE_INTFA:
            {
                struct intfa_frame *intfa_frame = &frame->f.intfa_frame;
                fprintf(output, "IntFA: #%d", intfa_frame->intfa - g->intfas);
                break;
            }
        }
        fprintf(output, ", start_offset: %d, eof_ok: %d\n", frame->start_offset, frame->eof_ok);
    }
    fprintf(output, "\n");
}
