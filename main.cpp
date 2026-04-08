#include <getopt.h>
#include <unistd.h>

#include <climits>
#include <cstdio>
#include <cstdlib>

#include "math.hpp"

struct calculator
{
    int firstnum = 0;
    int secondnum = 0;
    char operation = 0;
    long long result = 0;
    bool status_is_correct = true;
    bool help_asked = false;
};

void printhelp()
{
    printf("This calculator utility can do 6 math operations: \n");
    printf("addition, subtraction, multiplication, division, factorial, exponentiation.\n");

    printf(
        "To implement the math operation, you need to write the following data to the console "
        "using this kind of pattern:\n");

    printf(
        " ./build/calc first number: -f (number), second number: -s (number), operation -o "
        "(operation)\n");
        
    printf("except for factorial operation, which is need only first number and operation:\n");
    printf("./build/calc first number: -f (number), operation -o (operation)\n");
    printf("F.E addition of 5 and 10: ./build/calc -f 5 -s 10 -o '+'\n");
    printf("F.E factorial of 5: ./build/calc -f 5 -o '!'\n");
}

struct option help_option[] = 
{
    {"first", required_argument, 0, 'f'},
    {"second", required_argument, 0, 's'},
    {"operation", required_argument, 0, 'o'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};
void parse(int argc, char* argv[], calculator& calc1)
{
    int opt;
    bool hasFirst = false;
    bool hasSecond = false;
    bool hasOp = false;

    while ((opt = getopt_long(argc, argv, "f:s:o:h", help_option, NULL)) != -1)
    {
        switch (opt)
        {
            case 'f':
                calc1.firstnum = atoi(optarg);
                hasFirst = true;
                printf("first number = %d\n", calc1.firstnum);
                break;
            case 's':
                calc1.secondnum = atoi(optarg);
                hasSecond = true;
                printf("second number = %d\n", calc1.secondnum);
                break;
            case 'o':
                calc1.operation = optarg[0];
                hasOp = true;
                printf("operation = %c\n", calc1.operation);
                break;
            case 'h':
                calc1.help_asked = true;
                break;
            default:
                calc1.status_is_correct = false;
                printf("Unknown option: %c\n", (char)opt);
                break;
        }
    }

    if (!calc1.help_asked && !hasFirst)
    {
        calc1.status_is_correct = false;
        printf("Error: missing first number (-f)\n");
    }
    if (!calc1.help_asked && !hasOp)
    {
        calc1.status_is_correct = false;
        printf("Error: missing operation (-o)\n");
    }
    if (!calc1.help_asked && calc1.operation != '!' && !hasSecond)
    {
        calc1.status_is_correct = false;
        printf("Error: missing second number (-s)\n");
    }
}

void check(calculator& calc1)
{
    if (!calc1.status_is_correct)
        return;

    if (calc1.operation != '+' && calc1.operation != '-' && calc1.operation != '*' &&
        calc1.operation != '/' && calc1.operation != '^' && calc1.operation != '!')
    {
        calc1.status_is_correct = false;
        printf("Error: unknown operation '%c'\n", calc1.operation);
        return;
    }

    if (calc1.operation == '/' && calc1.secondnum == 0)
    {
        calc1.status_is_correct = false;
        printf("Error: division by zero!\n");
        return;
    }

    if (calc1.operation == '!' && calc1.firstnum < 0)
    {
        calc1.status_is_correct = false;
        printf("Error: factorial of negative number (%d)\n", calc1.firstnum);
        return;
    }

    printf("Check passed\n");
}

void calculate(calculator& calc1)
{
    if (!calc1.status_is_correct)
    {
        printf("Calculation skipped due to previous error\n");
        return;
    }

    bool overflow = false;

    if (calc1.operation == '+')
    {
        calc1.result = math::add(calc1.firstnum, calc1.secondnum, overflow);
        printf("Calc is calculating\n");
    }
    else if (calc1.operation == '-')
    {
        calc1.result = math::subtract(calc1.firstnum, calc1.secondnum, overflow);
        printf("Calc is calculating\n");
    }
    else if (calc1.operation == '*')
    {
        calc1.result = math::multiply(calc1.firstnum, calc1.secondnum, overflow);
        printf("Calc is calculating\n");
    }
    else if (calc1.operation == '/')
    {
        calc1.result = math::divide(calc1.firstnum, calc1.secondnum, overflow);
        printf("Calc is calculating\n");
    }
    else if (calc1.operation == '^')
    {
        calc1.result = math::exponentiation(calc1.firstnum, calc1.secondnum, overflow);
        printf("Calc is calculating\n");
    }
    else if (calc1.operation == '!')
    {
        calc1.result = math::factorial(calc1.firstnum, overflow);
        printf("Calc is calculating\n");
    }

    if (overflow)
    {
        calc1.status_is_correct = false;
        printf("Error: overflow during calculation!\n");
    }
}

void print(const calculator& calc1)
{
    if (!calc1.status_is_correct)
    {
        printf("Result: ERROR\n");
    }

    else
    {
        printf("Result: %lld\n", calc1.result);
    }
}

void run(int argc, char* argv[])
{
    calculator calc1;
    parse(argc, argv, calc1);
    if (calc1.help_asked)
    {
        printhelp();
        return;
    }
    check(calc1);
    calculate(calc1);
    print(calc1);
}

int main(int argc, char* argv[])
{
    run(argc, argv);
    return 0;
}