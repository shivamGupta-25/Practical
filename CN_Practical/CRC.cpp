#include <iostream>
using namespace std;

int main(){

    cout<<"Sender side"<<endl;
    cout<<"-----------------"<<endl;

    string msg, crc, encoded = "";
    cout << "Enter the message: ";
    getline(cin, msg);
    cout << "Enter the CRC generator polunomial: ";
    getline(cin, crc);

    int msg_len = msg.length();
    int crc_len = crc.length();
    encoded += msg;

    for (int i = 0; i < crc_len - 1; i++){
        encoded += '0';
    }
    // cout<< "Encoded message: " << encoded << endl;
    for (int i = 0; i <= encoded.length()-crc_len; ){
        for (int j = 0; j < crc_len; j++){
            encoded[i+j] = (encoded[i+j] == crc[j]) ? '0' : '1';
        }
        for ( ;i<encoded.length() && encoded[i] != '1'; i++);
    }
    //cout<< "Encoded message: " << encoded.substr(encoded.length()-crc_len+1) << endl;
    cout<< "Final message: " << msg + encoded.substr(encoded.length()-crc_len+1) << endl;

    cout<<"-----------------"<<endl;
    cout<<"Receiver side"<<endl;
    cout<<"-----------------"<<endl;

    string encoded_msg;
    cout << "Enter the received message: ";
    getline(cin, encoded_msg);

    for (int i = 0; i <= encoded_msg.length()-crc.length(); ){
        for (int j = 0; j < crc.length(); j++){
            encoded_msg[i+j] = (encoded_msg[i+j] == crc[j]) ? '0' : '1';
        }
        for ( ; i < encoded_msg.length() && encoded_msg[i] != '1'; i++);
    }
    // checking if the remainder is zero
    for ( char i: encoded_msg.substr(encoded_msg.length()-crc.length() ) ){
        if (i != '0'){
            cout<<endl<<"Error detected in the received message" << endl;
            return 0;
        }
    }
    cout<<endl<<"No error detected in the received message" << endl;
    return 0;
}