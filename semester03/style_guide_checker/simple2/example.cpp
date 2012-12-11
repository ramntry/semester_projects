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

class PrinterAsExampleOfClassWithLongCapitalizedCamelStyleNameBlahBlahBlah
{
public:
    void print(const char *message);
};

void PrinterAsExampleOfClassWithLongCapitalizedCamelStyleNameBlahBlahBlah::print(const char *)
{
    int x  = MACRO(CONSTANT);
}

void hello()
{
    PrinterAsExampleOfClassWithLongCapitalizedCamelStyleNameBlahBlahBlah printer;
    printer.print("hello");
}

int function_with_bad_comma_separated_list_of_args(int a, int b
        , int c, int d,
        int e, int f)
{
    return a + b + c + d + e + f;
}

struct Error {};
struct nameError {};

int main()
{
    hello();
}
