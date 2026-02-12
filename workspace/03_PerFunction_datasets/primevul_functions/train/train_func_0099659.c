static inline bool cpu_watchpoint_address_matches(CPUWatchpoint *wp,
                                                  vaddr addr,
                                                  vaddr len)
{


    vaddr wpend = wp->vaddr + wp->len - 1;
    vaddr addrend = addr + len - 1;

    return !(addr > wpend || wp->vaddr > addrend);
}
