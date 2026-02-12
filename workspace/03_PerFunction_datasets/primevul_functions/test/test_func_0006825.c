inline void sendCode(long long sCode, int runCount, long long runCode,
                     long long &c, int &lc, char *&out) {


  if (hufLength(sCode) + hufLength(runCode) + 8 < hufLength(sCode) * runCount) {
    outputCode(sCode, c, lc, out);
    outputCode(runCode, c, lc, out);
    outputBits(8, runCount, c, lc, out);
  } else {
    while (runCount-- >= 0) outputCode(sCode, c, lc, out);
  }
}
