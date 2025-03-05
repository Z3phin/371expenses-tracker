namespace lecture {

class A {

    private:
        int value;

    public:
        A();
        A(int value);
        ~A();
        
        void setValue(int value);

        int getValue() const {
            return value;
        }

        void doSomething() const;
    
};

}