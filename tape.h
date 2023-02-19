#ifndef TAPE
#define TAPE

#define OUT_OF_MEMORY 0
#define OK 1

class Tape {
private:
    int tick = 0;
    int size;
    int pointer;
    int elemAmount;
    int* elements;

    void Tick() {
        tick++;
    }

    void IncAmount() {
        elemAmount++;
    }

    void DecAmount() {
        elemAmount--;
    }

    void IncPtr() {
        pointer++;
    }

    void DecPtr() {
        pointer--;
    }

public:
    Tape(int sizeValue) {
        size = sizeValue;
        pointer = sizeValue - 1;
        elements = new int[sizeValue];
        elemAmount = 0;
    }

    int PopElement() {
        if (elements[pointer])
            DecAmount();
        int value = elements[pointer];
        elements[pointer] = 0;
        Tick();
        return value;
    }

    int GetElemetsAmount() {
        return elemAmount;
    }

    int GetTick() {
        return tick;
    }

    int GetElement() {
        Tick();
        return elements[pointer];
    }

    int Next() {
        Tick();
        if (pointer == 0)
            return OUT_OF_MEMORY;
        DecPtr();
        return OK;
    }

    int Previous() {
        Tick();
        if (pointer == size - 1)
            return OUT_OF_MEMORY;
        IncPtr();
        return OK;
    }


    void PutElement(int value) {
        Tick();
        IncAmount();
        elements[pointer] = value;
        DecPtr();
    }

    void MovePtrToStart() {
        while (pointer != size - 1)
            Previous();
    }

    void MovePtrToLastElem() {
        while (pointer != size - 1 && !elements[pointer])
            Previous();
        if (elements[pointer]) {
            while (pointer != 0 && elements[pointer])
                Next();
        }
    }

    ~Tape() {
        delete[] elements;
    }
};

#endif
