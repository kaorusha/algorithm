#include "huffman_codes.h"

int main ()
{
    HuffmanCodes test;
    if(!ReadData("../data/_eed1bd08e2fa58bbe94b24c06a20dcdb_huffman.txt", true, test))
        std::cout << "fail opening file";
    test.Run();
    return 0;
}