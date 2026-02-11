lmc_hssi_set_status (lmc_softc_t * const sc, lmc_ctl_t * ctl)
{
  if (ctl == NULL)
    {
      sc->lmc_media->set_clock_source (sc, sc->ictl.clock_source);
      lmc_set_protocol (sc, NULL);

      return;
    }


  if (ctl->clock_source && !sc->ictl.clock_source)
    {
      sc->lmc_media->set_clock_source (sc, LMC_CTL_CLOCK_SOURCE_INT);
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_INT;
    }
  else if (!ctl->clock_source && sc->ictl.clock_source)
    {
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_EXT;
      sc->lmc_media->set_clock_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
    }

  lmc_set_protocol (sc, ctl);
}
