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

class Printer
{
public:
    void print(const char *message);
};

void Printer::print(const char *)
{
}

void hello()
{
    Printer printer;
    printer.print("hello");
}

struct Error {};

int main()
{
    hello();
}
