run(void) {

    if (this != engine().worker(0))
      Support::Thread::sleep(Config::initial_delay);

    while (true) {
      switch (engine().cmd()) {
      case C_WAIT:

        engine().wait();
        break;
      case C_TERMINATE:

        engine().ack_terminate();

        engine().wait_terminate();

        engine().terminated();
        return;
      case C_RESET:

        engine().ack_reset_start();

        engine().wait_reset();

        engine().ack_reset_stop();
        break;
      case C_WORK:

        {
          m.acquire();
          if (idle) {
            m.release();

            find();
          } else if (cur != NULL) {
            start();
            if (stop(engine().opt())) {

              m.release();
              engine().stop();
            } else {
              node++;
              switch (cur->status(*this)) {
              case SS_FAILED:
                fail++;
                delete cur;
                cur = NULL;
                m.release();
                break;
              case SS_SOLVED:
                {

                  (void) cur->choice();
                  Space* s = cur->clone(false);
                  delete cur;
                  cur = NULL;
                  m.release();
                  engine().solution(s);
                }
                break;
              case SS_BRANCH:
                {
                  Space* c;
                  if ((d == 0) || (d >= engine().opt().c_d)) {
                    c = cur->clone();
                    d = 1;
                  } else {
                    c = NULL;
                    d++;
                  }
                  const Choice* ch = path.push(*this,cur,c);
                  cur->commit(*ch,0);
                  m.release();
                }
                break;
              default:
                GECODE_NEVER;
              }
            }
          } else if (path.next()) {
            cur = path.recompute(d,engine().opt().a_d,*this);
            m.release();
          } else {
            idle = true;
            path.ngdl(0);
            m.release();

            engine().idle();
          }
        }
        break;
      default:
        GECODE_NEVER;
      }
    }
  }
