#define CONSTANT 42
#define MACRO(n) (n * n)

class A
{
public:
   A() : a(10), b(20) {}

private:
   int a;
   int b;
   int mCorrect;
   int m_Uncorrect;
   int lalaala() { return 1; }

   class D {
      int aaaaaa() { return 0; }
   };

   char const *const MethodName() { return "hi"; }
   bool isCorrectBoolFunctionName() { return true; }
   bool uncorrectBoolFunctionName() { return true; }
};

class B : public A
{
public:
   B() : A(), c(30) {}

   int arrrrrrrr;
   class C {
      int dd;
   };

private:
   int c;
};

class PrinterAsExampleOfClassWithLongCapitalizedCamelStyleName
{
public:
    void print(const char *message);
};

void PrinterAsExampleOfClassWithLongCapitalizedCamelStyleName::print(const char *)
{
    int x = MACRO(CONSTANT);
}

void hello()
{
    PrinterAsExampleOfClassWithLongCapitalizedCamelStyleName printer;
    printer.print("hello");
}

struct Error {};
struct nameError {};

int main()
{
    hello();
}
