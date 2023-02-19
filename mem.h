#ifndef MEM
#define MEM

class MainMemory {
private:
    int size;
    int* memory;
public:
    explicit MainMemory(int sizeValue) {
        size = sizeValue;
        memory = new int[size];
    }

    bool compareTwoByAddr(int firstAddr, int secondAddr) {
        return memory[firstAddr] < memory[secondAddr];
    }

    void writeByAddr(int addr, int value) {
        memory[addr] = value;
    }

    ~MainMemory() {
        delete[] memory;
    }
};

#endif
