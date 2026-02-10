static int bad_mode_switch(CPUARMState *env, int mode, CPSRWriteType write_type) {
        ((env->uncached_cpsr & CPSR_M) == ARM_CPU_MODE_HYP ||
         mode == ARM_CPU_MODE_HYP)) {
            switch (mode) {
            case ARM_CPU_MODE_USR:
                return 0;
            case ARM_CPU_MODE_SYS:
            case ARM_CPU_MODE_SVC:
            case ARM_CPU_MODE_ABT:
            case ARM_CPU_MODE_UND:
            case ARM_CPU_MODE_IRQ:
            case ARM_CPU_MODE_FIQ:
