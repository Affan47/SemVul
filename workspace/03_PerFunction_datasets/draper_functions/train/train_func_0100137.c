listTopics(tColoredString &s, tString const &base, std::map<tString, eHelpTopic>::const_iterator begin, std::map<tString, eHelpTopic>::const_iterator const &end) {
        bool printed_start = false;
        for(;begin != end; ++begin) {
            if(!begin->first.StartsWith(base)) {
                continue;
            }

            if(begin->first.SubStr(base.Len() - 1).StrPos("_") >= 0) {

                continue;
            }
            if(!printed_start) {
                printed_start = true;
                s << tOutput("$help_topics_list_start");
            }
            s << tColoredString::ColorString(.5,.5,1.) << begin->first << tColoredString::ColorString(1.,1.,.5) << ": " << tOutput(&begin->second.m_shortdesc[0]) << "\n";
        }
    }
