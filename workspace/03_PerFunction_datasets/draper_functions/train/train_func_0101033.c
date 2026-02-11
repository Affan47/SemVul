GetJobDescription(const Job& job, std::string& desc_str) const {
    MCCConfig cfg;
    usercfg.ApplyToConfig(cfg);
    AREXClient ac(job.JobManagementURL, cfg, usercfg.Timeout(), false);
    if (ac.getdesc(job.IDFromEndpoint, desc_str)) {
      std::list<JobDescription> descs;
      if (JobDescription::Parse(desc_str, descs) && !descs.empty()) {
        return true;
      }
    }

    logger.msg(ERROR, "Failed retrieving job description for job: %s", job.JobID);
    return false;
  }
