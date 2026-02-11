t3(Wave4 &q, Wave4 &q1, Wave4 &q2,
			   Wave4 &q3, Wave4 &q4) {
  Wave4 omeQ(q2 + q3 + q4);
  Wave4 rhoQ(q3 + q4);
  double omeS = m2(omeQ);
  double rhoS = m2(rhoQ);


  double gM = sqrtpos(rhoM*rhoM - 4*picM*picM) * (rhoM*rhoM - 4*picM*picM)
    / rhoM;
  double dm = (rhoFormFactor1(0) - rhoFormFactor1(rhoM*rhoM) +
		 rhoM*rhoM * rhoFormFactor2(rhoM*rhoM)) / gM;
  return omeW * omeFormFactor(omeS) / (omeD(omeS) * rhoD(rhoS)) *
    pow2(omeM) * (rhoM*rhoM + rhoM*rhoG*dm) *
    ((m2(q,q3) * m2(q1,q4) - m2(q,q4) * m2(q1,q3)) * q2 +
     (m2(q,q4) * m2(q1,q2) - m2(q,q2) * m2(q1,q4)) * q3 +
     (m2(q,q2) * m2(q1,q3) - m2(q,q3) * m2(q1,q2)) * q4);

}
