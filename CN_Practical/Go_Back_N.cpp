#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h> // For sleep function

class GoBackNARQ {
private:
    struct Frame {
        char ack;
        int data;
    };

    std::vector<Frame> frames;
    int numFrames;
    int lostFrameIndex;

public:
    GoBackNARQ() : numFrames(0), lostFrameIndex(0) {}

    void sender() {
        std::cout << "Enter the number of Frames to be sent: ";
        std::cin >> numFrames;
        
        frames.resize(numFrames + 1); // +1 because the code uses 1-based indexing
        
        for (int i = 1; i <= numFrames; i++) {
            std::cout << "\nEnter the data for frame [" << i << "]: ";
            std::cin >> frames[i].data;
            frames[i].ack = 'Y';
        }
    }

    void simulateLostFrame() {
        // Generate a random index in range [1, numFrames]
        lostFrameIndex = 1 + (rand() % numFrames);
        frames[lostFrameIndex].ack = 'N';
        
        std::cout << "\nThe Frame number " << lostFrameIndex << " is not received\n";
    }

    void resendFrames() {
        std::cout << "\nResending From frame " << lostFrameIndex;
        for (int i = lostFrameIndex; i <= numFrames; i++) {
            sleep(2); // Using Unix sleep function
            frames[i].ack = 'Y';
            std::cout << "\nThe Received data of Frame " << i << " is " << frames[i].data;
        }
        std::cout << std::endl;
    }
    
    void run() {
        sender();
        simulateLostFrame();
        resendFrames();
        std::cout << "All frames sent Successfully\n";
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Initialize random seed
    
    std::cout << "=== Go-Back-N ARQ Protocol Simulation ===\n";
    
    GoBackNARQ protocol;
    protocol.run();
    
    std::cout << "\nSimulation completed.\n";
    
    return 0;
}