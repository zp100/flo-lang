# Flo

{...}

## General Syntax

{...}

## Identifiers

{...}

## Operators and Keywords

{...}

### Bitwise

Flo doesn't have dedicated operators for bitwise operations such as AND, OR, XOR, or bit shifting. These operations don't align with the high-level focus of the language enough to warrant their own operators, and would likely be rarely used in practice. If this functionality is still needed, the corresponding functions can be used instead: `bwand`, `bwor`, `bwnot`, `bwxor`, `bwsl`, `bwsr`, and `bwusr`.

### Piping

{...}

### Assignment

{...}

### Arithmetic

Flo supports the standard group of binary operators for simple arithmetic: `+`, `-`, `*`, `/`, and `%` for addition, subtraction, multiplication, division, and remainders. These follow the operator precedence rules of most other languages: `*`, `/`, and `%` are always evaluated before `+` and `-`. If equal-precedence operators are adjacent, they will be evaluated left-to-right.

Putting a `-` before a number will make it negative. (You can also put a `+` before a number, but this has no effect and is solely for visual clarity as-needed.)

In many languages, integer types and floating-point types are distinct, so any arithmetic operation on integers will produce an integer. This means that, in those languages, division will force the result to be an integer, even if that leads to a loss of data. For example, `10 / 4` might be truncated to `2`, instead of the expected `2.5`. In contrast, Flo will preserve the value after the decimal point, so it's always the full result: `10 / 4` evaluates to `2.5`. Be aware of this difference if you're used to integer division being truncated. If the goal is to actually get an integer result, you can reproduce the behavior by using functions such as `trunc` or `floor`, as in `10 / 4 | trunc` will give `2`.

For exponents, the `^` operator can be used. This has a couple key differences from the other 5 binary arithmetic operators, though. One distinction is that it will evaluate from right-to-left, whereas the previous operators are left-to-right (if they have equal precedence to each other). This means that an expression such as `2^3^2` will simplify the *right* side first to get `2^(9)`, which results in `512`, *not* `64`. Another difference is that `^` is evaluated before negation; the expression `-4^2` will become `-16`, *not* `16`. These rules match the rules of exponential expressions in math formulas.

### Comparisons

{...}

### Boolean Logic

{...}

### Ranges

{...}

### Operator Precedence

Precedence                  | Associativity | Operators
----------------------------|---------------|------------------
1\. Grouping                | N/A           | `(x)` Parentheses<br>`{ x }` Code block<br>`[ x ]` Collection literal
2\. Access                  | Left-to-right | `x[y]` Indexing
3\. Third-rank arithmetic   | Right-to-left | `x^y` Exponentiation
4\. Unary                   | N/A           | `+x` Positive<br>`-x` Negative<br>`not x` Logical NOT<br>`...x` Spread
5\. Type                    | Left-to-right | `x[y]` Indexing<br>`x<y>` Type declaration<br>`x<y -> z>` Function type declaration<br>`x as y` Type assertion<br>`x as y -> z` Function type assertion
6\. Second-rank arithmetic  | Left-to-right | `x * y` Multiplication<br>`x / y` Division<br>`x % y` Remainder
7\. First-rank arithmetic   | Left-to-right | `x + y` Addition<br>`x - y` Subtraction
8\. Comparison              | Left-to-right | `x == y` Equality<br>`x != y` Inequality<br>`x < y` Less than<br>`x > y` Greater than<br>`x <= y` Less than or equal<br>`x >= y` Greater than or equal<br>`x is y` Identity<br>`x is not y` Non-identity<br>`x in y` Membership<br>`x not in y` Non-membership
9\. Boolean                 | Left-to-right | `x and y` Logical AND<br>`x or y`Logical OR<br>`x else y` Null coalescense
10\. Ranges                  | N/A           | `x..y` Range (lower inclusive, upper exclusive)<br>`x..=y` Range (lower inclusive, upper inclusive)<br>`x..` Range (lower inclusive, upper unbounded)<br>`..y` Range (lower unbounded, upper exclusive)<br>`..=y` Range (lower unbounded, upper inclusive)<br>`x..y..z` Range with step (lower inclusive, upper exclusive)<br>`x..=y..z` Range with step (lower inclusive, upper inclusive)<br>`x....z` Range with step (lower inclusive, upper unbounded)<br>`..y..z` Range with step (lower unbounded, upper exclusive)<br>`..=y..z` Range with step (lower unbounded, upper inclusive)
11\. Lambda                 | Left-to-right | `x -> y` Anonymous function
12\. Structural             | Left-to-right | `x, y` Tuple separator<br>`x \| y` Pipe<br>`x ?\| y` Optional pipe<br>`x \| y: z` Pipe with callback<br>`x ?\| y: z` Optional pipe with callback
13\. Assignment             | Left-to-right | `x \|= def y` Constant initialization<br>`x \|= var y` Variable initialization<br>`x \|= y` Variable reassignment<br>`x \|^ y` `x \|* y` `x \|/ y` `x \|% y` `x \|+ y` `x \|- y`... Special variable reassignment<br>`def x: y` Callback constant initialization<br>`var x: y` Callback variable initialization<br>`x: y` Callback variable reassignment

## Type System

For any programming language, one of the main concerns for programmers is the language's type system. Differences in typing can have a dramatic impact on the performance and maintainability of a language's code.

Flo's typing is strongly-typed, static, nominal, and supports type inference and type casting. In essence, types are checked at compile time to help avoid unexpected errors, but are also robust enough to support a variety of use cases. Features such as tuples, generics, collections, and subsets make it possible to be as explicit as necessary with the values used at any point in a program.

### Types

Across all programming languages, there's a diverse variety in the types that are supported. However, these can be grouped into a handful of categories that are theoretically distinct:

- Unit: A single value that can't be used as an input for most operations. This would be equivalent to `void` in C or JavaScript.

- Null: A single value that *can* be used as an input, but lacks any meaningful data.

- Boolean: Values that only have two possible options, usually `true` and `false`, making them useful for conditional logic.

- Numeric: Values that represent points on the number line, for use in mathematical calculations.

- Text: Values for readable text, used as I/O between files, user input, and more. Some languages have a preference towards treating individual bytes or characters as values, such as C or Java, whereas some prefer to treat strings as essentially atomic, such as JavaScript or Python.

- Collective: Values that group other values together in a cohesive way. These sub-values can be of any type, even other collections. This category includes arrays, lists, dictionaries, sets, mappings, objects, class instances, structs, unions, ranges, etc.

- Any: Represents any value from the previous types, acting as a supertype of all others.

- Never: Asserts the lack of a value, as in a type that can never contain any value of any type. An example would be the `!` type in Rust.

Different programming languages break down these categories into different individual types. For example, C has a variety of numerical types, including `int`, `short int`, `long int`, `float`, `double`, and more. Kotlin has both `Char` and `String` as primitive types, whereas most languages have only one or the other. Collections of key-value pairs might be called `struct`, `dict`, `Map`, or `object` depending on the language, with nuanced differences between their behavior.

{...}

### Tuples

{...}

### Generics

{...}

## Classes

{...}

