OnDir(const wxString& dirname)
        {
            if (dirname == m_ExcludeDir)
                return wxDIR_IGNORE;
            if (m_Files.GetCount() == 1)
                return wxDIR_STOP;
            m_Files.Clear();
            return wxDIR_CONTINUE;
        }
