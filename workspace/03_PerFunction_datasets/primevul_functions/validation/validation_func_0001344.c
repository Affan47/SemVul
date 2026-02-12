void endFrame(const TypedValue* , const char* symbol,
                bool  = false) override {
    doTrace(symbol, true);
  }
