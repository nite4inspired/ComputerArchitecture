# 2.1 Writing a Simple Program

```run-c
#include <stdio.h>

int main(void)
{
	printf("To C, or not to C: that is the question.\n");
	return 0;
}
```

Preprocessor uses directives (# commands) to modify the program. This then goes to the compiler which translate it into object code (machine instructions). Finally, a linker combines the object code with additional code to yield a complete executable program. Additional code includes library functions (like printf) that are used in the program. (-o option allows to choose the name of the file containing the executable program)

# 2.2 The General Form of a Simple Program

```c
directives

int main(void)
{
	statements
}
```

Directives - editing commands that modify the program prior to compilation
Functions - blocks of executable code
Statements - commands to be performed when the program is run
## Directives

[[14 - The Preprocessor]] and [[15 - Writing Large Programs]] discuss directives in detail. For now, we only discuss the # include directive.

C has a number of headers like <stdio.h>. C has no built-in read and write commands. 

## Functions
Functions are either provided as part of the C implementation (library functions) or written by programmers. In C, a function is simply a series of statements that have been grouped together and given a name. **In Functional Programming, each function must return a value, C does not require this. (as opposed to something like Haskell)**

In computer programming, a pure function is a function that has the following properties:

1. the function return values are identical for identical arguments (no variation with local static variables, non-local variables, mutable reference arguments or input streams, i.e., referential transparency), and
2. the function has no side effects (no mutation of local static variables, non-local variables, mutable reference arguments or input/output streams).

main returns a status code that is given to the operating system when the program terminates. 

Program will still terminate without the return statement but it will produce a warning message. 

## Statements
A statement is a command to be executed. 
[[05 - Selection Statements]], [[06 - Loops]]

## Printing Strings
[[03 - Formatted Input Output]]
String Literal - a series of characters enclosed in double quotation marks. 
Must include \n (new line character) to advance to the next output line. 

# 2.3 Comments
Identifying Information to be included: program name, date, author, purpose, and so forth. 
```c
/*
*/
// C99 and on uses this
```

# 2.4 Variables and Assignment

## Types
Every variable must have a type. For now, we use int and float. Type affects how the variable is stored and what operations can be performed. 

In C you can use predefined macros from header files to get the limits for different numeric types. For example:

- For **integers**, include `<limits.h>` and use macros like `INT_MAX`, `LONG_MAX`, `UINT_MAX`, etc.
    
- For **floating-point numbers**, include `<float.h>` and use macros like `FLT_MAX` for floats or `DBL_MAX` for doubles.
    

### Example for an Integer

```run-c
#include <stdio.h>
#include <limits.h>

int main(void) 
{
    printf("The maximum value for an int is: %d\n", INT_MAX);
    return 0;
}
```

### Example for a Float

```run-c
#include <stdio.h>
#include <float.h>

int main(void) 
{
    printf("The maximum value for a float is: %e\n", FLT_MAX);
    return 0;
}
```

These macros are defined in the C standard libraries and provide the largest value that a given type can represent. This is the standard way in C to determine and print the limits of numeric variables.

In C you can find how close a float can get to 0 by using macros from `<float.h>`. There are two important values:

- **FLT_MIN:** This macro represents the smallest **normalized** positive floating-point number.
    
- **FLT_TRUE_MIN (C11 and later):** This macro gives the smallest positive floating-point number, including **subnormal** numbers (which are even closer to 0).
    

Here's an example:

```run-c
#include <stdio.h>
#include <float.h>

int main(void) 
{
    printf("Smallest normalized positive float (FLT_MIN): %e\n", FLT_MIN);
#ifdef FLT_TRUE_MIN
    printf("Smallest positive subnormal float (FLT_TRUE_MIN): %e\n", FLT_TRUE_MIN);
#endif
    return 0;
}
```

This code prints the smallest normalized float value using `FLT_MIN`, and if you're using a C11 compiler (or later) that supports subnormals, it will also print `FLT_TRUE_MIN` which is closer to 0 than `FLT_MIN`.

Arithmetic on float may be slower than arithmetic on int. The value of a float variable is often just an approximation of the number that was stored in it. 

> Most significantly, the value of a float variable is often just an approximation of the number that was stored in it. If we store 0.1 in a float variable, we may later find that the variable has a value such as 0.09999999999999987 , thanks to rounding error.

Floating-point numbers in C (and most other languages) follow the IEEE 754 standard, which uses binary fractions to represent values. Many numbers, such as 0.1, don’t have an exact binary equivalent. When you try to store 0.1, it gets converted to the closest binary approximation possible within the limited bits available. This inherent limitation leads to rounding errors that can show up when you print or perform arithmetic on the number.

In short, the value you see isn’t a mistake—it’s just the closest approximation the floating-point format can provide given its finite precision.

```run-c
#include <stdio.h>

int main(void) 
{
	float a = 0.1;
	printf("%.15e\n", a);
}
```

C doesn't include built-in support for arbitrary precision arithmetic like Python's `decimal.Decimal` or Java's `BigDecimal`. However, you can achieve this in C by using external libraries (GMP, MPFR).

## Declarations

Variables of same type can be declared together. As a matter of style, it's a good idea to leave a blank line between the declarations and the statements. Prior to C99 (i.e., in C89/C90), all variable declarations needed to appear at the beginning of a block before any executable statements. This meant you had to declare all variables at the start of functions or blocks, which could sometimes lead to less intuitive code structure. 

Type + Name

## Assignment

Numbers (like 8, 12, and 10) are said to be constants. Mixing types is discussed in [[04 - Expressions]].

## Printing the Value of a Variable

placeholders like %d, %f.. in printf string literal

## Initialization

Some variables are automatically set to zero when a program begins to execute, but most are not. A variable without a default value and no assigned value is uninitialized. Accessing an uninitialized variable may yield unpredictable result. 

Accessing an uninitialized variable in C is undefined behavior, meaning nothing is guaranteed to happen—it might seem to work, produce a wrong result, or crash. However, there are some specific situations where a crash is more likely:

- **Dereferencing Uninitialized Pointers:**  
    If you declare a pointer without initializing it, it may contain a garbage value. Dereferencing that pointer (for example, trying to write to or read from the location it points to) can lead to a segmentation fault or similar memory access violation.
    
- **Compiler and Debug Build Behavior:**  
    Some compilers, especially in debug mode (like Microsoft Visual Studio), deliberately fill uninitialized memory with a recognizable pattern (e.g., `0xCDCDCDCD`). This pattern can cause immediate crashes when used, which helps in catching bugs early. In contrast, release builds might not initialize variables at all, making the behavior unpredictable.
    
- **Runtime Tools and Sanitizers:**  
    Tools such as Valgrind or sanitizers enabled with GCC/Clang (like `-fsanitize=undefined`) can detect the use of uninitialized variables and abort the program or print error messages, effectively “crashing” the program when such undefined behavior is encountered.
    

So, while the C standard itself does not require a crash when accessing an uninitialized variable, certain conditions—such as dereferencing a garbage pointer or using debug instrumentation—can lead to an immediate crash in practice.

# 2.5 Reading Input

f in scanf or printf stands for "formatted." They use format strings. 

scanf("%d", &i); // reads an integer; stores into i 

Prompt normally shouldn't end with a new-line character. When the user presses the Enter key, the cursor automatically moves to the next line. 

# 2.6 Defining Names for Constants

macro definitions

```c
#define INCHES_PER_POUND 166
```

this is a directive so semicolon is not needed. INCHES_PER_POUND is the macro. Macros in C are handled by the preprocessor before the actual compilation begins. The preprocessor scans your code for macro definitions (e.g., `#define`) and performs a textual replacement, inserting the defined values or code snippets wherever the macro appears. 

The upper-case letters is a convention. 

# 2.7 Identifiers

Identifiers in C are the names you assign to variables, functions, types, etc. Their rules have evolved slightly over the years, but here’s an overview:

---

### General Rules (All Versions)

- **Allowed Characters:**  
    An identifier must start with a letter (a–z or A–Z) or an underscore (`_`). Subsequent characters can be letters, digits (0–9), or underscores.
    
- **Case Sensitivity:**  
    Identifiers are case-sensitive, so `var`, `Var`, and `VAR` are considered different.
    
- **Reserved Names:**  
    Identifiers beginning with an underscore followed by an uppercase letter, or with two underscores, are reserved for the implementation (such as the compiler or standard library).
    

---

### C89/C90 (ANSI C)

- **Syntax:**  
    The rules for allowed characters and case sensitivity are as described above.
    
- **Significance of Characters:**  
    The standard required that an implementation must recognize at least the first **31 characters** of an identifier for distinguishing names. (Historically, some older systems limited external identifiers to as few as 6 characters, but the minimum requirement per the standard was 31 for portability.)
    

---

### C99 and Later (C99, C11, C18)

- **Syntax:**  
    The basic syntax (starting with a letter or underscore and then letters, digits, or underscores) remains the same.
    
- **Universal Character Names:**  
    C99 introduced support for universal character names (e.g., `\uXXXX` or `\UXXXXXXXX`), allowing identifiers to include Unicode characters. This extension supports internationalization, provided the characters fall into allowed categories (like letters).
    
- **Increased Identifier Significance:**  
    The standard mandates that implementations must treat at least **63 characters** as significant for internal identifiers and at least **31 characters** for external identifiers. This means that when distinguishing between identifiers, compilers should consider up to 63 characters in the identifier (for internal linkage), which improves over the older limit.
    

---

### Summary

- **Before C99:**  
    Identifiers consisted of letters, digits, and underscores, had a minimum of 31 significant characters, and did not support Unicode directly.
    
- **C99 and Later:**  
    The syntax remains largely the same, but with the addition of universal character names for Unicode support and increased minimum significance (63 characters for internal identifiers).
    

These rules ensure that identifiers are predictable and portable across different C implementations while allowing compilers some flexibility beyond the minimum requirements.

```run-c
#include <stdio.h>

int main(void) 
{
    int \uD55C\uAD6D\uC778 = 100; // \uD55C = 한, \uAD6D = 국, \uC778 = 인
    printf("The value is: %d\n", \uD55C\uAD6D\uC778);
    return 0;
}
```

```run-c
#include <stdio.h>

int main(void) 
{
    int 한국인 = 100;
    printf("The value is: %d\n", 한국인);
    return 0;
}
```

Below is an overview of the standard C keywords by version. Note that many compilers also support extensions beyond these lists, but the following are those defined by the language standards.

---

### C89/C90 Keywords (32 Keywords)

- **auto**
- **break**
- **case**
- **char**
- **const**
- **continue**
- **default**
- **do**
- **double**
- **else**
- **enum**
- **extern**
- **float**
- **for**
- **goto**
- **if**
- **int**
- **long**
- **register**
- **return**
- **short**
- **signed**
- **sizeof**
- **static**
- **struct**
- **switch**
- **typedef**
- **union**
- **unsigned**
- **void**
- **volatile**
- **while**

---

### C99 Additional Keywords (5 Additional Keywords)

C99 introduced a few new keywords to support features like inline functions and new types for boolean and complex arithmetic:

- **inline**
- **restrict**
- **_Bool**
- **_Complex**
- **_Imaginary**

This brings the total in C99 to 37 keywords.

---

### C11 (and C18) Additional Keywords (7 Additional Keywords)

C11 added several keywords to support new features such as generic selections, atomic operations, and thread-local storage:

- **_Alignas**
- **_Alignof**
- **_Atomic**
- **_Generic**
- **_Noreturn**
- **_Static_assert**
- **_Thread_local**

This brings the total in C11/C18 to 44 keywords.

---

### Summary

- **C89/C90:** 32 keywords
- **C99:** Adds 5 keywords (total 37)
- **C11/C18:** Adds 7 keywords (total 44)

These keywords are reserved and cannot be used as identifiers in your code. They form the core of the language's syntax and support the features defined by each standard version.

# 2.8 Layout of a C Program

> We can think of a C program as a series of tokens: groups of characters that can't be split up without changing their meaning. 

Identifiers, keywords, operators, punctuation marks(, ; parentheses), and string literals. 

Space between tokens isn't critical in most cases. Tokens can be put together unless it merges them into a token. 

Putting { } on separate lines makes them easy to spot since they pair up. 

Adding a new-line character in a string is illegal. 

## Q & A

C standard replaces `/* */` with a single space character. 

Stepping through the program line by line with a debugger will reveal if any lines are being skipped (for example, for unterminated comment). Some IDEs display comments in color. Usually the program will throw an error since comments don't follow the syntax. 

Can nest `//` but not `/* */`

Compilers are only required to remember certain number of characters (31 for C89 and 63 for C99). There are special rules for identifiers with external linkage [[18 - Declarations]]. Most function names fall into this category. Some older linkers can handle only short names. 

Older C standards imposed limits on how many characters in an identifier had to be significant, which affected external identifiers (the ones used for linking). Here's a summary:

---

**C89/C90 (ANSI C):**

- **External Identifiers:**  
    Linkers must distinguish identifiers based on at least the first **6 characters**.  
    (For example, if you have two functions named `foobar` and `foobaz`, an old linker might treat them as the same if only the first 6 characters are used for differentiation.)
    
- **Internal Identifiers:**  
    Within a function or block scope, at least the first **31 characters** are significant.
    

---

**C99 and Later (C99/C11/C18):**

- **External Identifiers:**  
    The requirement was increased so that linkers must consider at least the first **31 characters** of an identifier.  
    This change reduces the chance of name collisions in larger projects.
    
- **Internal Identifiers:**  
    For identifiers with block scope, at least the first **63 characters** must be significant.
    

---

These requirements represent the minimum guaranteed by the standards for compatibility and portability. In practice, most modern compilers and linkers support much longer identifiers, but when targeting or maintaining legacy systems, these limits might still be relevant.

In virtually all modern C environments that follow IEEE‑754 with proper rounding, both

```c
float a = 2.1234567890123456789f;
float b = 2.1234567890123456789;
```

end up with the same final float value. This is because:

- The literal with the **f** suffix is immediately parsed and rounded to the nearest representable float.
    
- The literal without the suffix is parsed as a double (with higher precision) and then converted (rounded) to a float using the same round‑to‑nearest rule.
    

**Can They Ever Differ?**

In theory, if you have a number that falls exactly halfway between two representable float values, the rounding might be sensitive to the extra precision available when the literal is first parsed as a double. On some older systems—especially those using x87 floating‑point hardware with 80‑bit extended registers—the extra internal precision could, in very contrived cases, lead to a slightly different rounding result when the double is eventually converted to float. However, in modern environments (using, for example, SSE registers), both methods yield identical results.

**An Attempt at a Contrived Example**

One might try to force a difference by choosing a borderline value. Consider this code:

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    // Borderline value chosen for illustration
    float a = 1.0000000596046448f;   // parsed as float directly
    float b = 1.0000000596046448;     // parsed as double, then converted

    // Print with enough precision to observe differences
    printf("a: %.20f\n", a);
    printf("b: %.20f\n", b);

    // Compare the bit representations
    if (memcmp(&a, &b, sizeof(a)) != 0)
        printf("a and b differ in memory representation.\n");
    else
        printf("a and b are identical.\n");

    return 0;
}
```

On most modern systems, you will find that `a` and `b` print the same value and their bit representations are identical. If any difference appears, it would be an artifact of a particular platform’s floating‑point handling (such as extended precision on x87 hardware) or non‑standard compiler behavior.

**Summary**

- **In practice:** They almost always yield the same float value.
    
- **Best Practice:** Use the **f** suffix when you want a float literal to avoid any ambiguity and potential warnings.
    
- **Edge Cases:** Differences are theoretical and very system‑dependent, occurring only in extreme borderline cases or on older platforms with extended precision registers.
    

Thus, while it’s possible to contrive scenarios where a difference might occur, for all practical purposes in modern C programming the two forms are equivalent.

# Exercises

1. 
```run-c
#include <stdio.h>

int main(void) 
{
	printf("hello, world\n");
}
```
2. Skip
3. Skip
4. 
```run-c
#include <stdio.h>

int main(void) 
{
	int a, b;
	float c, d;
	printf("%d\n%d\n%.7f\n%.7f\n", a, b, c, d);
	return 0;
}
```
5. a) 100_bottles
6. reader can confuse betwee `_` and `__`.
7. a, e / If is capitalized, main is not a keyword, printf is a library function name
Here's an example showing that **main** isn't a reserved keyword by using it as a local variable and as a structure member:

### Example 1: Local Variable Named main

```run-c
#include <stdio.h>

int main(void) {
    // Here, 'main' is a local variable, not the entry point.
    int main = 42;
    printf("Local variable 'main': %d\n", main);
    return 0;
}
```

### Example 2: Structure Member Named main

```run-c
#include <stdio.h>

struct Data {
    int main;  // 'main' used as a member of a structure.
};

int main(void) {
    struct Data d;
    d.main = 99;
    printf("Structure member 'main': %d\n", d.main);
    return 0;
}
```

In both examples, **main** is used in a different scope than the program's entry point. Although these are legal in C, using **main** for anything other than the entry function can be confusing and is generally discouraged.

8. 14
9. skip
10. skip

## Projects

1. skip
2. skip
3. skip
4. 
```run-c
#include <stdio.h>

int main(void)
{
	printf("Enter an amount: ");
	float a;
	scanf("%f", &a);
	printf("Wtih tax added: %.2f", 1.05 * a);
	return 0;
}
```
5. skip
6. 
```run-c
#include <stdio.h>

int main(void)
{
	printf("Enter a value for x: ");
	float a;
	scanf("%f", &a);
	printf("3x^5 + 2x^4 - 3x^2 + 5x - 1 = %.2f\n", (((3*a + 2)*a*a-3)*a+5)-1 );
	return 0;
}
```