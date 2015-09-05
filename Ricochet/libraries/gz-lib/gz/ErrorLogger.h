#ifndef ERRORLOGGER_H_INCLUDED
#define ERRORLOGGER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <ctime>

namespace gz
{

    void log_error(std::string error_message);

    inline void log_error(std::string error_message)
    {
        //time_t rawtime;
        //struct tm * timeinfo;
        //char timestringbuffer [80];

        //time (&rawtime);
        //timeinfo = localtime (&rawtime);

        //strftime (timestringbuffer,80,"[%d/%m/%Y %I:%M:%S%p]",timeinfo);

        std::ofstream errorLog;
		std::string errorMessage = "";//timestringbuffer;
        errorMessage += "\t";
        errorMessage += error_message;
        errorLog.open("log.txt",std::ios::out | std::ios::app);
        if ( errorLog.is_open() )
        {
            errorLog << "Error" << "\t" << error_message << "\n";
            //std::cout << "Error: " << errorMessage << std::endl;
        }
        std::cout << errorMessage << std::endl;
        errorLog.close();
    }

}

#endif // ERRORLOGGER_H_INCLUDED
