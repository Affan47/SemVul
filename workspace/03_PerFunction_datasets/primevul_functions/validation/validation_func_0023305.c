void cpu_check_watchpoint(CPUState *cpu, vaddr addr, vaddr len,
                          MemTxAttrs attrs, int flags, uintptr_t ra)
{
    CPUClass *cc = CPU_GET_CLASS(cpu);
    CPUWatchpoint *wp;

    assert(tcg_enabled());
    if (cpu->watchpoint_hit) {


        qemu_mutex_lock_iothread();
        cpu_interrupt(cpu, CPU_INTERRUPT_DEBUG);
        qemu_mutex_unlock_iothread();
        return;
    }

    if (cc->tcg_ops->adjust_watchpoint_address) {

        addr = cc->tcg_ops->adjust_watchpoint_address(cpu, addr, len);
    }
    QTAILQ_FOREACH(wp, &cpu->watchpoints, entry) {
        if (watchpoint_address_matches(wp, addr, len)
            && (wp->flags & flags)) {
            if (replay_running_debug()) {


                if (!cpu->can_do_io) {

                    cpu->cflags_next_tb = 1 | CF_LAST_IO | CF_NOIRQ | curr_cflags(cpu);
                    cpu_loop_exit_restore(cpu, ra);
                }


                replay_breakpoint();
                return;
            }
            if (flags == BP_MEM_READ) {
                wp->flags |= BP_WATCHPOINT_HIT_READ;
            } else {
                wp->flags |= BP_WATCHPOINT_HIT_WRITE;
            }
            wp->hitaddr = MAX(addr, wp->vaddr);
            wp->hitattrs = attrs;

            if (wp->flags & BP_CPU && cc->tcg_ops->debug_check_watchpoint &&
                !cc->tcg_ops->debug_check_watchpoint(cpu, wp)) {
                wp->flags &= ~BP_WATCHPOINT_HIT;
                continue;
            }
            cpu->watchpoint_hit = wp;

            mmap_lock();

            tb_check_watchpoint(cpu, ra);
            if (wp->flags & BP_STOP_BEFORE_ACCESS) {
                cpu->exception_index = EXCP_DEBUG;
                mmap_unlock();
                cpu_loop_exit(cpu);
            } else {

                cpu->cflags_next_tb = 1 | CF_LAST_IO | CF_NOIRQ | curr_cflags(cpu);
                mmap_unlock();
                cpu_loop_exit_noexc(cpu);
            }
        } else {
            wp->flags &= ~BP_WATCHPOINT_HIT;
        }
    }
}
