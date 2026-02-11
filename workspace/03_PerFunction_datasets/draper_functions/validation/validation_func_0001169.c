getNodeLabel(const MachineBasicBlock *Node,
                             const MachineFunction *Graph) {
      if (isSimple () && Node->getBasicBlock() &&
          !Node->getBasicBlock()->getName().empty())
        return Node->getBasicBlock()->getNameStr() + ":";

      std::string OutStr;
      {
        raw_string_ostream OSS(OutStr);

        if (isSimple())
          OSS << Node->getNumber() << ':';
        else
          Node->print(OSS);
      }

      if (OutStr[0] == '\n') OutStr.erase(OutStr.begin());


      for (unsigned i = 0; i != OutStr.length(); ++i)
        if (OutStr[i] == '\n') {
          OutStr[i] = '\\';
          OutStr.insert(OutStr.begin()+i+1, 'l');
        }
      return OutStr;
    }
  }
