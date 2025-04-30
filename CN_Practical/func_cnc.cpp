#include <iostream>
using namespace std;

// Function to perform XOR division with CRC polynomial
string xorDivision(string data, const string& divisor) {
    int data_len = data.length();
    int divisor_len = divisor.length();
    
    // Perform XOR division
    for (int i = 0; i <= data_len - divisor_len; ) {
        // If the current bit is 1, perform XOR with divisor
        if (data[i] == '1') {
            for (int j = 0; j < divisor_len; j++) {
                data[i+j] = (data[i+j] == divisor[j]) ? '0' : '1';
            }
        }
        i++;
        while (i < data_len && data[i] != '1') {
            i++;
        }
    }
    return data;
}

// Function for sender side operations
string senderCRC(const string& msg, const string& crc) {
    int msg_len = msg.length();
    int crc_len = crc.length();
    string encoded = msg;
    
    // Append zeros equal to polynomial length-1
    for (int i = 0; i < crc_len - 1; i++) {
        encoded += '0';
    }
    
    // Use the XOR division function
    encoded = xorDivision(encoded, crc);
    
    // Get the remainder (CRC checksum)
    string remainder = encoded.substr(encoded.length() - crc_len + 1);
    
    // Return the original message with CRC remainder appended
    return msg + remainder;
}

// Function for receiver side operations
bool receiverCRC(const string& encoded_msg, const string& crc) {
    // Use the XOR division function for checking
    string result = xorDivision(encoded_msg, crc);
    
    // Checking if the remainder is zero
    string remainder = result.substr(result.length() - crc.length() + 1);
    
    // Check if all bits in remainder are zero
    for (char bit : remainder) {
        if (bit != '0') {
            return false;  // Error detected
        }
    }
    
    return true;  // No error detected
}

int main(){
    cout << "Sender side" << endl;
    cout << "-----------------" << endl;

    string msg, crc;
    cout << "Enter the message: ";
    getline(cin, msg);
    cout << "Enter the CRC generator polynomial: ";
    getline(cin, crc);

    // Process sender side
    string final_message = senderCRC(msg, crc);
    cout << "Final message: " << final_message << endl;

    cout << "-----------------" << endl;
    cout << "Receiver side" << endl;
    cout << "-----------------" << endl;

    string received_msg;
    cout << "Enter the received message: ";
    getline(cin, received_msg);

    // Process receiver side
    bool is_valid = receiverCRC(received_msg, crc);
    
    if (is_valid) {
        cout << endl << "No error detected in the received message" << endl;
    } else {
        cout << endl << "Error detected in the received message" << endl;
    }
    
    return 0;
}