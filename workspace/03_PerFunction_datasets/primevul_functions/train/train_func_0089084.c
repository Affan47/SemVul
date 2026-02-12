static bool isinfinity(T x) {
    using namespace fmt::internal;


    if (const_check(sizeof(isinf(x)) != sizeof(fmt::internal::DummyInt))) {
      return isinf(x) != 0;
    }
    return !_finite(static_cast<double>(x));
  }
