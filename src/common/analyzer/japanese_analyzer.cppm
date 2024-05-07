//
// Created by jjk on 24-5-7.
//

module;

export module japanese_analyzer;

import stl;
import term;
import analyzer;
import third_party;

namespace infinity {

export class JapaneseAnalyzer : public Analyzer{
public:
    JapaneseAnalyzer(const String &path);

    JapaneseAnalyzer(const JapaneseAnalyzer &other);

    ~JapaneseAnalyzer();

    bool Load();

};

}