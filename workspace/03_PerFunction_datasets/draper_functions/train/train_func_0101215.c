bench_malloc(size_t n)
{
     void *p;
     if (n == 0) n = 1;

#if defined(WITH_OUR_MALLOC)


     {
	  void *p0;
	  if ((p0 = malloc(n + MIN_ALIGNMENT))) {
	       p = (void *) (((size_t) p0 + MIN_ALIGNMENT) & (~((size_t) (MIN_ALIGNMENT - 1))));
	       *((void **) p - 1) = p0;
	  }
	  else
	       p = (void *) 0;
     }
#elif defined(HAVE_MEMALIGN)
     p = memalign(MIN_ALIGNMENT, n);
#elif defined(HAVE_POSIX_MEMALIGN)


     if (posix_memalign(&p, MIN_ALIGNMENT, n))
	  p = (void*) 0;
#elif defined(__ICC) || defined(__INTEL_COMPILER) || defined(HAVE__MM_MALLOC)

     p = (void *) _mm_malloc(n, MIN_ALIGNMENT);
#    undef real_free
#    define real_free _mm_free
#else
     p = malloc(n);
#endif

     BENCH_ASSERT(p);
     return p;
}
