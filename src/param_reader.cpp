#include <param_reader.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

namespace {

    void tokenizeLine(string *paramName,
                      string *paramValue,
                      const string &line)
    {
        if(!paramName || !paramValue)
            return;

        using namespace boost;

        vector<string> tokens;
        split(tokens, line, is_any_of(": "),token_compress_on);

        if(tokens.size() > 0)
            *paramName = tokens[0];

        if(tokens.size() > 1)
            *paramValue = tokens[1];
    }

}

namespace aasoni {

ParamReader::ParameterType ParamReader::paramNameToType(const string &paramName)
{
    if(paramName == "")
        return EMPTY_LINE;
    else if(paramName == "DATA_FILE_NAME")
        return DATA_FILE_NAME;
    else if(paramName == "WAVE_AMPLITUDE")
        return WAVE_AMPLITUDE;
    else if(paramName == "WAVE_SIGMA_X")
        return WAVE_SIGMA_X;
    else if(paramName == "WAVE_SIGMA_Y")
        return WAVE_SIGMA_Y;
    else if(paramName == "WAVE_X")
        return WAVE_X;
    else if(paramName == "WAVE_Y")
        return WAVE_Y;
    else if(paramName == "WAVE_C")
        return WAVE_C;
    else if(paramName == "X_LENGTH")
        return X_LENGTH;
    else if(paramName == "Y_LENGTH")
        return Y_LENGTH;
    else if(paramName == "STEPS")
        return STEPS;
    else if(paramName == "DELTA_X")
        return DELTA_X;
    else if(paramName == "DELTA_Y")
        return DELTA_Y;
    else if(paramName == "DELTA_T")
        return DELTA_T;
    else if(paramName == "//")
        return COMMENT;
    else
        return UNKNOWN_TYPE;

}

void ParamReader::readParameter(const string &line)
{
    string paramName, paramValue;
    tokenizeLine(&paramName, &paramValue, line);
    ParameterType type = paramNameToType(paramName);

    std::stringstream ss;
    switch(type)
    {
        case EMPTY_LINE:
            //ignore
            break;
        case DATA_FILE_NAME:
            m_dataFileName = paramValue;
            break;
        case WAVE_AMPLITUDE:
            ss << paramValue;
            ss >> m_wAmplitude;
            break;
        case WAVE_SIGMA_X:
            ss << paramValue;
            ss >> m_wSigmaX;
            break;
        case WAVE_SIGMA_Y:
            ss << paramValue;
            ss >> m_wSigmaY;
            break;
        case WAVE_X:
            ss << paramValue;
            ss >> m_wX;
            break;
        case WAVE_Y:
            ss << paramValue;
            ss >> m_wY;
            break;
        case WAVE_C:
            ss << paramValue;
            ss >> m_wC;
            break;
        case X_LENGTH:
            ss << paramValue;
            ss >> m_xLength;
            break;
        case Y_LENGTH:
            ss << paramValue;
            ss >> m_yLength;
            break;
        case STEPS:
            ss << paramValue;
            ss >> m_steps;
        case DELTA_X:
            ss << paramValue;
            ss >> m_deltaX;
        case DELTA_Y:
            ss << paramValue;
            ss >> m_deltaY;
        case DELTA_T:
            ss << paramValue;
            ss >> m_deltaT;
        case COMMENT:
            //nothing to do
            break;
        default:
            //unknow type skip
            break;
    }
}

ParamReader::ParamReader(const string &parameterFileName)
{
    ifstream fhandle(parameterFileName.c_str(), ifstream::in);

    string line;
    while(getline(fhandle, line))
        readParameter(line);
}

} //aasoni
