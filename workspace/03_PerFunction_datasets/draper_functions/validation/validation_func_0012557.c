GetParity(OBMol& mol, map<OBAtom*, MDLFormat::Parity> &parity)
  {

    std::vector<OBGenericData*> vdata = mol.GetAllData(OBGenericDataType::StereoData);
    for (std::vector<OBGenericData*>::iterator data = vdata.begin(); data != vdata.end(); ++data)
      if (((OBStereoBase*)*data)->GetType() == OBStereo::Tetrahedral) {
        OBTetrahedralStereo *ts = dynamic_cast<OBTetrahedralStereo*>(*data);

        OBTetrahedralStereo::Config cfg = ts->GetConfig();

        Parity atomparity = Unknown;
        if (cfg.specified && cfg.winding != OBStereo::UnknownWinding) {


          OBStereo::Refs refs = cfg.refs;

          unsigned long maxref = OBStereo::NoRef;

          if (cfg.from != OBStereo::ImplicitRef && mol.GetAtomById(cfg.from)->IsHydrogen())
            maxref = cfg.from;
          else
            for (OBStereo::RefIter ref_it = refs.begin(); ref_it != refs.end(); ++ref_it)
              if ((*ref_it) != OBStereo::ImplicitRef && mol.GetAtomById(*ref_it)->IsHydrogen())
                maxref = *ref_it;

          if (maxref == OBStereo::NoRef)
            maxref = std::max(*(std::max_element(refs.begin(), refs.end())), cfg.from);


          cfg = ts->GetConfig(maxref, OBStereo::Clockwise, OBStereo::ViewTowards);
          int inversions = OBStereo::NumInversions(cfg.refs);


          if (inversions % 2 == 0)
            atomparity = Clockwise;
          else
            atomparity = AntiClockwise;
        }
        parity[mol.GetAtomById(cfg.center)] = atomparity;
      }
  }
