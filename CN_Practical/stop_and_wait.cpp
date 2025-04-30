#include <iostream>
#include <cstdlib>    // For rand() and srand()
#include <unistd.h>   // For sleep() function
#include <ctime>      // For time() function

using namespace std;

int main() {
    // Seed random number generator
    srand(time(NULL));
    
    int i, j, packet[30];
    int fsize = (rand() % 16) + 1; // Random size of the packet
    
    cout << "\n\t Frame Size: " << fsize << endl;
    cout << "\n\t -- Data Log -- " << endl;
    cout << "\n Frame \t Data\twaiting\tAcknowledgement\tresend" << endl;

    for (i = 0; i < fsize; i++) {
        packet[i] = rand() % 1000;
        cout << "\n " << i+1 << " \t " << packet[i];
        
        j = 0; // Initialize j before using it
        while (j == 0 || rand() % 2 == 0) // Fixed comparison operator
        {
            sleep(1);
            cout << "\t1 ";
            sleep(1);
            
            for(j = 2; rand() % 2 == 0 && j < 4; j++) {
                cout << " " << j;
                sleep(1);
            }
            
            if (j == 4) {
                cout << "\t NO \tResending...\n " << i+1 << " \t " << packet[i];
                j = 0; // Reset j to continue the outer while loop
            }
            else {
                break;
            }
        }
        
        if (j == 0) {
            sleep(1);
            cout << "\t0 ";
        }
        
        cout << "\t YES \t No";
    }

    cout << "\n\n\t -- All Data Packet sent -- \n" << endl;

    return 0;
}