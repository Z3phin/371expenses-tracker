void main() {

    // ptr has junk value
    int *ptr = new int;
    *ptr = 42;
    delete ptr;
    ptr = nullptr;

    // ptr2 has value 0
    int *ptr2 = new int();
    delete ptr2;
    ptr2 = nullptr;

    // ptr3 has value 4
    int *ptr3 = new int(4);
    delete ptr3;
    ptr3 = nullptr;

    // ptr4 is an array of junk values
    int *ptr4 = new int[10];
    delete [] ptr4;
    ptr4 = nullptr;

    // ptr5 is a zeroed array
    int *ptr5 = new int[10]();
    for (int i = 0; i < 10; i++) {
        ptr5[i] = 42;
    }
    delete [] ptr5;
    ptr5 = nullptr;


}