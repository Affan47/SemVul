int seccomp_memory_deny_write_execute(void) {

        uint32_t arch;
        int r;

        SECCOMP_FOREACH_LOCAL_ARCH(arch) {
                _cleanup_(seccomp_releasep) scmp_filter_ctx seccomp = NULL;
                int filter_syscall = 0, block_syscall = 0, shmat_syscall = 0;

                log_debug("Operating on architecture: %s", seccomp_arch_to_string(arch));

                switch (arch) {

                case SCMP_ARCH_X86:
                        filter_syscall = SCMP_SYS(mmap2);
                        block_syscall = SCMP_SYS(mmap);
                        break;

                case SCMP_ARCH_PPC64:
                case SCMP_ARCH_PPC64LE:
                        filter_syscall = SCMP_SYS(mmap);


                        break;

                case SCMP_ARCH_ARM:
                        filter_syscall = SCMP_SYS(mmap2);
                        shmat_syscall = SCMP_SYS(shmat);
                        break;

                case SCMP_ARCH_X86_64:
                case SCMP_ARCH_X32:
                case SCMP_ARCH_AARCH64:
                        filter_syscall = SCMP_SYS(mmap);
                        shmat_syscall = SCMP_SYS(shmat);
                        break;


#if !defined(__i386__) && !defined(__x86_64__) && !defined(__powerpc64__) && !defined(__arm__) && !defined(__aarch64__)
#warning "Consider adding the right mmap() syscall definitions here!"
#endif
                }


                if (filter_syscall == 0)
                        continue;

                r = seccomp_init_for_arch(&seccomp, arch, SCMP_ACT_ALLOW);
                if (r < 0)
                        return r;

                r = add_seccomp_syscall_filter(seccomp, arch, filter_syscall,
                                               1,
                                               SCMP_A2(SCMP_CMP_MASKED_EQ, PROT_EXEC|PROT_WRITE, PROT_EXEC|PROT_WRITE));
                if (r < 0)
                        continue;

                if (block_syscall != 0) {
                        r = add_seccomp_syscall_filter(seccomp, arch, block_syscall, 0, (const struct scmp_arg_cmp){} );
                        if (r < 0)
                                continue;
                }

                r = add_seccomp_syscall_filter(seccomp, arch, SCMP_SYS(mprotect),
                                               1,
                                               SCMP_A2(SCMP_CMP_MASKED_EQ, PROT_EXEC, PROT_EXEC));
                if (r < 0)
                        continue;

#ifdef __NR_pkey_mprotect
                r = add_seccomp_syscall_filter(seccomp, arch, SCMP_SYS(pkey_mprotect),
                                               1,
                                               SCMP_A2(SCMP_CMP_MASKED_EQ, PROT_EXEC, PROT_EXEC));
                if (r < 0)
                        continue;
#endif

                if (shmat_syscall != 0) {
                        r = add_seccomp_syscall_filter(seccomp, arch, SCMP_SYS(shmat),
                                                       1,
                                                       SCMP_A2(SCMP_CMP_MASKED_EQ, SHM_EXEC, SHM_EXEC));
                        if (r < 0)
                                continue;
                }

                r = seccomp_load(seccomp);
                if (IN_SET(r, -EPERM, -EACCES))
                        return r;
                if (r < 0)
                        log_debug_errno(r, "Failed to install MemoryDenyWriteExecute= rule for architecture %s, skipping: %m", seccomp_arch_to_string(arch));
        }

        return 0;
}
