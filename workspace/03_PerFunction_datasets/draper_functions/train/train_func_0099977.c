_eina_cpu_count_internal(void)
{
#ifdef EFL_HAVE_THREADS

# if   defined (_WIN32)
   SYSTEM_INFO sysinfo;

   GetSystemInfo(&sysinfo);
   return sysinfo.dwNumberOfProcessors;

# elif defined (__sun) || defined(__GNU__)


   return sysconf(_SC_NPROCESSORS_ONLN);

# elif defined (__FreeBSD__) || defined (__OpenBSD__) || \
   defined (__NetBSD__) || defined (__DragonFly__) || defined (__MacOSX__) || \
   (defined (__MACH__) && defined (__APPLE__))

   int mib[4];
   int cpus;
   size_t len = sizeof(cpus);

   mib[0] = CTL_HW;
#ifdef HW_AVAILCPU
   mib[1] = HW_AVAILCPU;
#else
   mib[1] = HW_NCPU;
#endif
   sysctl(mib, 2, &cpus, &len, NULL, 0);
   if (cpus < 1)
      cpus = 1;

   return cpus;

# elif defined (__linux__) || defined(__GLIBC__)
   cpu_set_t cpu;
   int i;
   static int cpus = 0;

   if (cpus != 0)
      return cpus;

   CPU_ZERO(&cpu);
   if (sched_getaffinity(0, sizeof(cpu), &cpu) != 0)
     {
        fprintf(stderr, "[Eina] could not get cpu affinity: %s\n",
                strerror(errno));
        return 1;
     }

   for (i = 0; i < TH_MAX; i++)
     {
        if (CPU_ISSET(i, &cpu))
           cpus = i + 1;
        else
           break;
     }
   return cpus;

# else
#  error "eina_cpu_count() error: Platform not supported"
# endif
#else
   return 1;
#endif
}
