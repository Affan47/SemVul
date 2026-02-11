dy_prtlpphase (dyphase_enum phase, bool abbrv)


{ const char *rtnnme = "dy_prtlpphase" ;

  switch (phase)
  { case dyINIT:
    { return ((abbrv == TRUE)?"IN":"initialisation") ; }
    case dyPURGEVAR:
    { return ((abbrv == TRUE)?"VD":"variable deactivation") ; }
    case dyGENVAR:
    { return ((abbrv == TRUE)?"VG":"variable generation") ; }
    case dyADDVAR:
    { return ((abbrv == TRUE)?"VA":"variable activation") ; }
    case dyPRIMAL1:
    { return ((abbrv == TRUE)?"P1":"primal phase I") ; }
    case dyPRIMAL2:
    { return ((abbrv == TRUE)?"P2":"primal phase II") ; }
    case dyPURGECON:
    { return ((abbrv == TRUE)?"CD":"constraint deactivation") ; }
    case dyGENCON:
    { return ((abbrv == TRUE)?"CG":"constraint generation") ; }
    case dyADDCON:
    { return ((abbrv == TRUE)?"CA":"constraint activation") ; }
    case dyDUAL:
    { return ((abbrv == TRUE)?"D2":"dual") ; }
    case dyFORCEDUAL:
    { return ((abbrv == TRUE)?"FD":"force dual") ; }
    case dyFORCEPRIMAL:
    { return ((abbrv == TRUE)?"FP":"force primal") ; }
    case dyFORCEFULL:
    { return ((abbrv == TRUE)?"FF":"force full") ; }
    case dyDONE:
    { return ((abbrv == TRUE)?"DN":"done") ; }
    case dyINV:
    { return ((abbrv == TRUE)?"NV":"invalid") ; }
    default:
    { errmsg(6,rtnnme,"lp phase",(int) phase) ;
      return ((abbrv == TRUE)?"??":"nonsense") ; } } }
