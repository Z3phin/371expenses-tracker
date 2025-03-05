class A {

    private:
        int value;

    public:
        A();    // Constructor
        A(int value);   // Overloaded constructor
        ~A();       // Destructor


        void setValue(int value);

        int getValue() const {
            return value;
        }

        void doSomething() const;
};

