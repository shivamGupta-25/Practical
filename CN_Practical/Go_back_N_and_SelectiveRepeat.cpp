#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h> // For sleep function

class ARQProtocol {
protected:
    struct Frame {
        char ack;
        int data;
    };

    std::vector<Frame> frames;
    int numFrames;
    int lostFrameIndex;

public:
    // Common functionality
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

    virtual void resendFrames() = 0; // Pure virtual function to be implemented by derived classes
    
    void run() {
        sender();
        simulateLostFrame();
        resendFrames();
        std::cout << "All frames sent Successfully\n";
    }
};

class SelectiveRepeatARQ : public ARQProtocol {
public:
    void resendFrames() override {
        std::cout << "\nResending the frame " << lostFrameIndex;
        sleep(2); // Using Unix sleep function
        frames[lostFrameIndex].ack = 'Y';
        std::cout << "\nThe Received Frame is " << frames[lostFrameIndex].data << std::endl;
    }
};

class GoBackNARQ : public ARQProtocol {
public:
    void resendFrames() override {
        std::cout << "\nResending From frame " << lostFrameIndex;
        for (int i = lostFrameIndex; i <= numFrames; i++) {
            sleep(2); // Using Unix sleep function
            frames[i].ack = 'Y';
            std::cout << "\nThe Received data of Frame " << i << " is " << frames[i].data;
        }
        std::cout << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Initialize random seed
    
    int choice;
    do {
        std::cout << "\n\n1. Selective Repeat ARQ\n2. Go-Back-N ARQ\n3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                SelectiveRepeatARQ protocol;
                protocol.run();
                break;
            }
            case 2: {
                GoBackNARQ protocol;
                protocol.run();
                break;
            }
            case 3:
                std::cout << "Exiting program...\n";
                return 0;
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 3);
    
    return 0;
}