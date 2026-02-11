setChiral(int index, Smiley::Chirality chirality, const std::vector<int> &chiralNbrs)
    {


      unsigned long center = indices[index] - 1;
      unsigned long from = indices[chiralNbrs[0]] - 1;
      std::vector<unsigned long> refs(chiralNbrs.size() - 1);
      for (std::size_t i = 0; i < refs.size(); ++i)
        if (chiralNbrs[i + 1] == Smiley::implicitHydrogen())
          refs[i] = OBStereo::ImplicitRef;
        else
          refs[i] = indices[chiralNbrs[i + 1]] - 1;


      switch (chirality) {
        case Smiley::Clockwise:
          switch (chiralNbrs.size()) {
            case 4:
              OBTetrahedralStereo *stereo = new OBTetrahedralStereo(mol);
              stereo->SetConfig(OBTetrahedralStereo::Config(center, from, refs));
              mol->SetData(stereo);
              break;
          }
          break;
        case Smiley::AntiClockwise:
          switch (chiralNbrs.size()) {
            case 4:
              OBTetrahedralStereo *stereo = new OBTetrahedralStereo(mol);
              stereo->SetConfig(OBTetrahedralStereo::Config(center, from, refs, OBStereo::AntiClockwise));
              mol->SetData(stereo);
              break;
          }
          break;
      }
    }
