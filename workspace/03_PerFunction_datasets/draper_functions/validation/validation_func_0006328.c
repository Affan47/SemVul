when(Home home, BoolVar x,
       void (*t)(Space& home), void (*e)(Space& home),
       IntConLevel) {
    if (home.failed()) return;
    GECODE_ES_FAIL(Int::Exec::When::post(home,x,t,e));
  }

}
