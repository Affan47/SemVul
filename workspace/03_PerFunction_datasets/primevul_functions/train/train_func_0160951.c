void NumberFormatTest::TestUFormattable(void) {
  {

    UErrorCode status = U_ZERO_ERROR;
    LocalUFormattablePointer defaultUFormattable(ufmt_open(&status));
    assertSuccess("calling umt_open", status);
    Formattable defaultFormattable;
    assertTrue((UnicodeString)"comparing ufmt_open() with Formattable()",
               (defaultFormattable
                == *(Formattable::fromUFormattable(defaultUFormattable.getAlias()))));
    assertTrue((UnicodeString)"comparing ufmt_open() with Formattable()",
               (defaultFormattable
                == *(Formattable::fromUFormattable(defaultUFormattable.getAlias()))));
    assertTrue((UnicodeString)"comparing Formattable() round tripped through UFormattable",
               (defaultFormattable
                == *(Formattable::fromUFormattable(defaultFormattable.toUFormattable()))));
    assertTrue((UnicodeString)"comparing &Formattable() round tripped through UFormattable",
               ((&defaultFormattable)
                == Formattable::fromUFormattable(defaultFormattable.toUFormattable())));
    assertFalse((UnicodeString)"comparing &Formattable() with ufmt_open()",
               ((&defaultFormattable)
                == Formattable::fromUFormattable(defaultUFormattable.getAlias())));
    testFormattableAsUFormattable(__FILE__, __LINE__, defaultFormattable);
  }

  {
    Formattable f(ucal_getNow(), Formattable::kIsDate);
    testFormattableAsUFormattable(__FILE__, __LINE__,  f);
  }
  {
    Formattable f((double)1.61803398874989484820);
    testFormattableAsUFormattable(__FILE__, __LINE__,  f);
  }
  {
    Formattable f((int64_t)80994231587905127LL);
    testFormattableAsUFormattable(__FILE__, __LINE__,  f);
  }
  {
    Formattable f((int32_t)4);
    testFormattableAsUFormattable(__FILE__, __LINE__,  f);
  }
  {
    Formattable f("Hello world.");
    testFormattableAsUFormattable(__FILE__, __LINE__,  f);
  }
  {
    UErrorCode status2 = U_ZERO_ERROR;
    Formattable f(StringPiece("73476730924573500000000.0"), status2);
    assertSuccess("Constructing a StringPiece", status2);
    testFormattableAsUFormattable(__FILE__, __LINE__,  f);
  }
  {
    UErrorCode status2 = U_ZERO_ERROR;
    UObject *obj = new Locale();
    Formattable f(obj);
    assertSuccess("Constructing a Formattable from a default constructed Locale()", status2);
    testFormattableAsUFormattable(__FILE__, __LINE__,  f);
  }
  {
    const Formattable array[] = {
      Formattable(ucal_getNow(), Formattable::kIsDate),
      Formattable((int32_t)4),
      Formattable((double)1.234),
    };

    Formattable fa(array, 3);
    testFormattableAsUFormattable(__FILE__, __LINE__, fa);
  }
}
