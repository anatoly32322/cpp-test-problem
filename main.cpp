#include <iostream>
#include "mem.h"
#include "tape.h"

MainMemory mem = MainMemory(2);

void sortTape(Tape* inputTape, Tape* minAuxTape, Tape* maxAuxTape, Tape* outputTape) {
    inputTape->MovePtrToStart();
    if (inputTape->GetElemetsAmount() == 0)
        return;
    if (inputTape->GetElemetsAmount() == 1) {
        int first = inputTape->PopElement();
        outputTape->MovePtrToLastElem();
        outputTape->PutElement(first);
        return;
    }
    minAuxTape->MovePtrToLastElem();
    maxAuxTape->MovePtrToLastElem();
    while (true) {
        int first = inputTape->PopElement();
        inputTape->Next();
        int second = inputTape->PopElement();
        inputTape->Next();
        if (first == 0 && second == 0)
            break;
        if (second == 0) {
            minAuxTape->PutElement(first);
            minAuxTape->Next();
            break;
        }
        mem.writeByAddr(0, first);
        mem.writeByAddr(1, second);
        if (mem.compareTwoByAddr(0, 1)) {
            minAuxTape->PutElement(first);
            maxAuxTape->PutElement(second);
        }
        else {
            minAuxTape->PutElement(second);
            maxAuxTape->PutElement(first);
        }
    }
    sortTape(minAuxTape, inputTape, maxAuxTape, outputTape);
    sortTape(maxAuxTape, minAuxTape, inputTape, outputTape);
}

int main(int argc, char** argv) {
    if (argc == 3) {
        if (!freopen(argv[1], "r", stdin)){
            std::cout << "Wrong filepath.\n";
            return -1;
        }
        if (!freopen(argv[2], "w+", stdout)){
            std::cout << "Wrong filepath.\n";
            return -1;
        }
    }
    int n;
    int x;
    std::cin >> n;
    Tape inputTape = Tape(n);
    for(int i = 0; i < n; i++) {
        std::cin >> x;
        inputTape.PutElement(x);
    }
    inputTape.MovePtrToStart();
    Tape firstAuxTape = Tape(n);
    Tape secondAuxTape = Tape(n);
    Tape outputTape = Tape(n);
    sortTape(&inputTape, &firstAuxTape, &secondAuxTape, &outputTape);
    outputTape.MovePtrToStart();
    for (int i = 0; i < n; i++) {
        std::cout << outputTape.GetElement() << ' ';
        outputTape.Next();
    }
    int ticks = inputTape.GetTick() + firstAuxTape.GetTick() + secondAuxTape.GetTick() + outputTape.GetTick();
    std::cout << "\nticks: " << ticks;
    fclose(stdout);
    return 0;
}
