#include <scaledataparser.h>

void PrintHelp()
{
    std::cout << "C++ Data Parser for Pacific Scale - MT-Data Trial" << std::endl;
    std::cout << "Usage: scaleparser [-h|--help]" << std::endl;
    std::cout << "                   [-p|--port <path>] [-b|--baud <number>]" << std::endl;
    std::cout << "                   [-i|--interval <time(s) [default: 10]>]" << std::endl;
}


int main(int argc, char *argv[])
{
    std::string portPath = "";
    int baudRate = 0;
    int printInterval = 10;
    
    
    // If no argument was given, print help
    if (argc < 2)
    {
        PrintHelp();
        return 0;
    }

    // Loop through all the command line arguments
    for (int indx = 1; indx < argc; indx++)
    {
        std::string currentArg = std::string(argv[indx]);
        
        if (currentArg == "-h" || currentArg == "--help")
        {
            PrintHelp();
            return 0;
        }

        // Check for serial port flag
        else if (currentArg == "-p" || currentArg == "--port")
        {
            // Made sure that a path was actually provided.
            if (indx + 1 <= argc-1)
                portPath = std::string(argv[indx+1]);
            else
            {
                std::cout << "Error: You did not provide a path to the serial port." << std::endl;
                PrintHelp();
                return -1;
            }
        }

        // Check for baud rate flag
        else if (currentArg == "-b" || currentArg == "--baud")
        {
            // Made sure that a baud rate was actually provided.
            if (indx + 1 <= argc-1)
                baudRate = atoi(argv[indx+1]);
            else
            {
                std::cout << "Error: You did not provide a baud rate." << std::endl;
                PrintHelp();
                return -1;
            }
        }

        // Check for print interval time flag
        else if (currentArg == "-i" || currentArg == "--interval")
        {
            // Made sure that an interval was actually provided.
            if (indx + 1 <= argc-1)
                printInterval = atoi(argv[indx+1]);
            else
            {
                std::cout << "Error: You did not provide an interval time." << std::endl;
                PrintHelp();
                return -1;
            }
        }
    }

    // Make sure that enough arguments are provided
    if (portPath.empty())
    {
        std::cout << "Error: You did not provide a path to the serial port." << std::endl;
        PrintHelp();
        return -1;
    }
    else if (!baudRate)
    {
        std::cout << "Error: You did not provide a baud rate." << std::endl;
        PrintHelp();
        return -1;
    }

    try
    {
        setupSignalHandling();
        ScaleDataParser parser(portPath, baudRate, printInterval);
        std::cout << "Initalised parser! Serial port: " << parser.Port();
        std::cout << " | Baud rate: " << parser.Baud() << std::endl;
        
        parser.RunParser();
        return 0;
    }
    
    catch(std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    
};