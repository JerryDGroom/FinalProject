#include <iostream>
#include "Scheduler.h"
using namespace std;

void print_help()
{
    cout << endl << "Commands:" << endl;
    cout << "  H       : Help (displays this message)" << endl;
    cout << "  R       : Run the Program" << endl;
    cout << "  Q       : Quit the test program" << endl;
    cout << endl;
    cout << endl;
    cout << "============================================================================" << endl;
    cout << "** In order to quit program during process of inputting patient and doctor" << endl;
    cout << "** information. Type a Capitol 'Q' and <enter> twice to get back to " << endl;
    cout << "** the Help menu." << endl;
    cout << "============================================================================" << endl;
    cout << endl;

}

int main()
{

    char cmd;                     // Input command
    print_help();
    Scheduler testProgram;
    //return 0;

    do
    {
        cout << endl << "Command (H for help): ";                 // Read command
        cin >> cmd;
        cmd = toupper( cmd );			     // Normalize to upper case


        switch ( cmd )
        {
        case 'H' :
            print_help();
            break;

        case 'R' :                                 // Begin Program
            testProgram.start();
            break;

        case 'Q' :                              // Quit test program
            break;

        default :                               // Invalid command
            cout << "Invalid command" << endl;
        }
    }
    while ( cmd != 'Q' );

    return 0;
}



