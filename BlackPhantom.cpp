#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

// === Abstract Base Class ===
class Encoder {
public:
    virtual string encode(const string& input) = 0;  // Polymorphism
    virtual ~Encoder() {}
};

// === Derived Class (Base64) ===
class Base64Encoder : public Encoder {
private:
    string base64_chars;

public:
    Base64Encoder() {
        base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    }

    string encode(const string& input) override {
        string output;
        int val = 0, valb = -6;
        for (unsigned char c : input) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                output.push_back(base64_chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) output.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (output.size() % 4) output.push_back('=');
        return output;
    }
};

// === DNS Formatter Class ===
class DNSFormatter {
public:
    string format(const string& input, int blockSize = 18) {
        stringstream ss;
        for (size_t i = 0; i < input.size(); i++) {
            ss << input[i];
            if ((i + 1) % blockSize == 0 && (i + 1) != input.size()) {
                ss << ".";
            }
        }
        return ss.str();
    }
};

// === User Tool Class ===
class PhantomBlackTool {
private:
    Encoder* encoder;
    DNSFormatter formatter;

public:
    PhantomBlackTool(Encoder* enc) : encoder(enc) {}

    void run() {
        string input;
        cout << "\n?? Welcome to BlackPhantom DNS Tool ??\n";
        cout << "Enter string to encode & format: ";
        getline(cin, input);

        string encoded = encoder->encode(input);
        string formatted = formatter.format(encoded);

        cout << "\nBase64 Encoded: " << encoded << endl;
        cout << "DNS Format    : " << formatted << endl;
    }
};

// === Main Menu ===
int main() {
    Base64Encoder base64;
    PhantomBlackTool tool(&base64);

    int choice;
    do {
        cout << "\n====== BlackPhantom Menu ======\n";
        cout << "1. Encode and Format String\n";
        cout << "2. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            tool.run();
        } else if (choice != 2) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 2);

    cout << "Goodbye, Red Teamer!\n";
    return 0;
}

