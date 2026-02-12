static void assemble_file(const char *fname, StrList **depend_ptr)
{
    char *line;
    insn output_ins;
    int i;
    uint64_t prev_offset_changed;
    int64_t stall_count = 0;

    switch (cmd_sb) {
    case 16:
        break;
    case 32:
        if (!iflag_cpu_level_ok(&cmd_cpu, IF_386))
            nasm_fatal(0, "command line: 32-bit segment size requires a higher cpu");
        break;
    case 64:
        if (!iflag_cpu_level_ok(&cmd_cpu, IF_X86_64))
            nasm_fatal(0, "command line: 64-bit segment size requires a higher cpu");
        break;
    default:
        panic();
        break;
    }

    prev_offset_changed = nasm_limit[LIMIT_PASSES];
    for (passn = 1; pass0 <= 2; passn++) {
        pass1 = pass0 == 2 ? 2 : 1;
        pass2 = passn > 1  ? 2 : 1;


        globalbits = cmd_sb;
        cpu = cmd_cpu;
        if (pass0 == 2) {
	    lfmt->init(listname);
        } else if (passn == 1 && listname && !keep_all) {

            remove(listname);
        }
        in_absolute = false;
        global_offset_changed = 0;
        if (passn > 1) {
            saa_rewind(forwrefs);
            forwref = saa_rstruct(forwrefs);
            raa_free(offsets);
            offsets = raa_init();
        }
        location.segment = NO_SEG;
        location.offset  = 0;
        if (passn == 1)
            location.known = true;
        ofmt->reset();
        switch_segment(ofmt->section(NULL, pass2, &globalbits));
        preproc->reset(fname, pass1, pass1 == 2 ? depend_ptr : NULL);


	memcpy(warning_state, warning_state_init, sizeof warning_state);

        globallineno = 0;

        while ((line = preproc->getline())) {
            if (++globallineno > nasm_limit[LIMIT_LINES])
                nasm_fatal(0,
                           "overall line count exceeds the maximum %"PRId64"\n",
                           nasm_limit[LIMIT_LINES]);


            if (process_directives(line))
                goto end_of_line;


            parse_line(pass1, line, &output_ins);

            if (optimizing.level > 0) {
                if (forwref != NULL && globallineno == forwref->lineno) {
                    output_ins.forw_ref = true;
                    do {
                        output_ins.oprs[forwref->operand].opflags |= OPFLAG_FORWARD;
                        forwref = saa_rstruct(forwrefs);
                    } while (forwref != NULL
                             && forwref->lineno == globallineno);
                } else
                    output_ins.forw_ref = false;

                if (output_ins.forw_ref) {
                    if (passn == 1) {
                        for (i = 0; i < output_ins.operands; i++) {
                            if (output_ins.oprs[i].opflags & OPFLAG_FORWARD) {
                                struct forwrefinfo *fwinf = (struct forwrefinfo *)saa_wstruct(forwrefs);
                                fwinf->lineno = globallineno;
                                fwinf->operand = i;
                            }
                        }
                    }
                }
            }


            if (output_ins.opcode == I_EQU) {
                if (!output_ins.label) {
                    nasm_error(ERR_NONFATAL, "EQU not preceded by label");
                } else if (output_ins.operands == 1 &&
                           (output_ins.oprs[0].type & IMMEDIATE) &&
                           output_ins.oprs[0].wrt == NO_SEG) {
                    define_label(output_ins.label,
                                 output_ins.oprs[0].segment,
                                 output_ins.oprs[0].offset, false);
                } else if (output_ins.operands == 2
                           && (output_ins.oprs[0].type & IMMEDIATE)
                           && (output_ins.oprs[0].type & COLON)
                           && output_ins.oprs[0].segment == NO_SEG
                           && output_ins.oprs[0].wrt == NO_SEG
                           && (output_ins.oprs[1].type & IMMEDIATE)
                           && output_ins.oprs[1].segment == NO_SEG
                           && output_ins.oprs[1].wrt == NO_SEG) {
                    define_label(output_ins.label,
                                 output_ins.oprs[0].offset | SEG_ABS,
                                 output_ins.oprs[1].offset, false);
                } else {
                    nasm_error(ERR_NONFATAL, "bad syntax for EQU");
                }
            } else {
                int32_t n;

                nasm_assert(output_ins.times >= 0);

                for (n = 1; n <= output_ins.times; n++) {
                    if (pass1 == 1) {
                        int64_t l = insn_size(location.segment,
                                              location.offset,
                                              globalbits, &output_ins);


                        if (using_debug_info)
                        {

                            int32_t typeinfo =
                                TYS_ELEMENTS(output_ins.operands);
                            switch (output_ins.opcode) {
                            case I_RESB:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_BYTE;
                                break;
                            case I_RESW:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_WORD;
                                break;
                            case I_RESD:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_DWORD;
                                break;
                            case I_RESQ:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_QWORD;
                                break;
                            case I_REST:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_TBYTE;
                                break;
                            case I_RESO:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_OWORD;
                                break;
                            case I_RESY:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_YWORD;
                                break;
                            case I_RESZ:
                                typeinfo =
                                    TYS_ELEMENTS(output_ins.oprs[0].offset) | TY_ZWORD;
                                break;
                            case I_DB:
                                typeinfo |= TY_BYTE;
                                break;
                            case I_DW:
                                typeinfo |= TY_WORD;
                                break;
                            case I_DD:
                                if (output_ins.eops_float)
                                    typeinfo |= TY_FLOAT;
                                else
                                    typeinfo |= TY_DWORD;
                                break;
                            case I_DQ:
                                typeinfo |= TY_QWORD;
                                break;
                            case I_DT:
                                typeinfo |= TY_TBYTE;
                                break;
                            case I_DO:
                                typeinfo |= TY_OWORD;
                                break;
                            case I_DY:
                                typeinfo |= TY_YWORD;
                                break;
                            case I_DZ:
                                typeinfo |= TY_ZWORD;
                                break;
                            default:
                                typeinfo = TY_LABEL;
                                break;
                            }

                            dfmt->debug_typevalue(typeinfo);
                        }


                        if (l != -1) {
                            increment_offset(l);
                        }


                    } else {
                        if (n == 2)
                            lfmt->uplevel(LIST_TIMES);
                        increment_offset(assemble(location.segment,
                                                  location.offset,
                                                  globalbits, &output_ins));
                    }
                }
            }
            if (output_ins.times > 1)
                lfmt->downlevel(LIST_TIMES);

            cleanup_insn(&output_ins);

        end_of_line:
            nasm_free(line);
        }

        if (global_offset_changed && !terminate_after_phase) {
            switch (pass0) {
            case 1:
                nasm_error(ERR_WARNING|ERR_WARN_PHASE,
                           "phase error during stabilization pass, hoping for the best");
                break;

            case 2:
                nasm_error(ERR_NONFATAL,
                           "phase error during code generation pass");
                break;

            default:

                break;
            }
        }

        if (pass1 == 1)
            preproc->cleanup(1);


        if ((passn > 1 && !global_offset_changed) || pass0 > 0) {
            pass0++;
        } else if (global_offset_changed &&
                   global_offset_changed < prev_offset_changed) {
            prev_offset_changed = global_offset_changed;
            stall_count = 0;
        } else {
            stall_count++;
        }

        if (terminate_after_phase)
            break;

        if ((stall_count > nasm_limit[LIMIT_STALLED]) ||
            (passn >= nasm_limit[LIMIT_PASSES])) {


             nasm_error(ERR_NONFATAL,
                          "Can't find valid values for all labels "
                          "after %"PRId64" passes, giving up.", passn);
             nasm_error(ERR_NONFATAL,
                        "Possible causes: recursive EQUs, macro abuse.");
             break;
        }
    }

    preproc->cleanup(0);
    lfmt->cleanup();
    if (!terminate_after_phase && opt_verbose_info) {

        fprintf(stdout, "info: assembly required 1+%"PRId64"+1 passes\n",
                passn-3);
    }
}
