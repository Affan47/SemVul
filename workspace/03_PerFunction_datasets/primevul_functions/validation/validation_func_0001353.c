void validateStack(TraceIterator tIt, Stats& stats) {
    auto enteredName = m_stack.back().trace->symbol;
    auto exitedName = tIt->symbol;
    if ((exitedName != nullptr) &&
        ((enteredName == nullptr) || (strcmp(enteredName, exitedName) != 0))) {


      if ((enteredName != nullptr) &&
          ((strncmp(enteredName, "run_init::", 10) == 0) ||
           (strcmp(enteredName, "_") == 0))) return;
      bool fixed = false;
      if (m_stack.size() > 1) {
        auto callerName = (m_stack.end() - 2)->trace->symbol;
        if ((callerName != nullptr) && (strcmp(callerName, exitedName) == 0)) {


          m_stack.pop_back();
          fixed = true;
        }
      }


      if (++m_badArcCount < 20) {
        std::string badArc;
        if (fixed) {
          badArc = folly::format("(warning: corrected bad arc #{}: "
                                 "enter '{}', exit '{}')",
                                 m_badArcCount,
                                 enteredName, exitedName).str();
        } else {
          badArc = folly::format("(error: bad arc #{}: "
                                 "enter '{}', exit '{}')",
                                 m_badArcCount,
                                 enteredName, exitedName).str();
        }
        ++stats[badArc.data()].count;
      }
    }
  }
