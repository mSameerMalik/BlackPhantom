# BlackPhantom 👻

BlackPhantom is a lightweight red team tool written in C++ for Kali Linux. It encodes any string using Base64, splits the result into 18-character blocks, and inserts dots for DNS-safe exfiltration.

##  Features
- Base64 Encoding
- DNS Label-Safe Output
- 18-character chunking
- Simple console UI
- Fully object-oriented C++

##  How to Compile

```bash
g++ -o blackphantom blackphantom.cpp
./blackphantom
