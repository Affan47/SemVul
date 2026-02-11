init_attributes()
{

  verbosity = new Integer("sim.verbosity",1,"gpsim's verboseness 0=nothing printed 0xff=very verbose");
  globalSymbolTable().addSymbol(verbosity);
  globalSymbolTable().addSymbol(new CycleCounterAttribute());
  stop_watch = new StopWatch;
#ifdef HAVE_GUI
  globalSymbolTable().addSymbol(new GUIUpdateRateAttribute());
#endif

  globalSymbolTable().addSymbol(new Integer("POR_RESET",  POR_RESET));
  globalSymbolTable().addSymbol(new Integer("WDT_RESET",  WDT_RESET));
  globalSymbolTable().addSymbol(new Integer("IO_RESET",   IO_RESET));
  globalSymbolTable().addSymbol(new Integer("SOFT_RESET", SOFT_RESET));
  globalSymbolTable().addSymbol(new Integer("BOD_RESET",  BOD_RESET));
  globalSymbolTable().addSymbol(new Integer("SIM_RESET",  SIM_RESET));
  globalSymbolTable().addSymbol(new Integer("MCLR_RESET", MCLR_RESET));

}
