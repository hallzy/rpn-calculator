# RPN Calculator

RPN Calculator for the terminal.

* Currently supports a stack size of 128
* Numerous mathematical functions

## Table of Contents

* [Install](#install)
* [Run Tests](#run-tests)
* [Usage](#usage)
  * [Entering Hex, Octal, or Binary Numbers](#entering-hex-octal-or-binary-numbers)
    * [Decimal](#decimal)
    * [Hexadecimal](#hexadecimal)
    * [Octal](#octal)
    * [Binary](#binary)
* [Supported Operations](#supported-operations)
  * [Stack Manipulations](#stack-manipulations)
    * [Duplicate Stack Element](#duplicate-stack-element)
    * [Drop Element From the Stack](#drop-element-from-the-stack)
    * [Swap Stack Elements](#swap-stack-elements)
    * [Clear the stack](#clear-the-stack)
  * [Calculator Settings](#calculator-settings)
    * [Change Angle Mode](#change-angle-mode)
    * [Change Numeric Base](#change-numeric-base)
  * [Math Operations](#math-operations)
    * [Basic Arithmetic](#basic-arithmetic)
    * [Exponents and Radicals](#exponents-and-radicals)
    * [Absolute Values](#absolute-values)
    * [Reciprocation](#reciprocation)
    * [Trigonometric Functions](#trigonometric-functions)
    * [Logarithmic Functions](#logarithmic-functions)
    * [Sums of Groups of Numbers](#sums-of-groups-of-numbers)
    * [Operations on Specified Stack Entries](#operations-on-specified-stack-entries)
    * [Factorial](#factorial)
    * [Fibonacci](#fibonacci)
  * [Mathematical Constants](#mathematical-constants)
    * [π](#π)
    * [e](#e)
  * [Bitwise Operations](#bitwise-operations)
    * [Bitwise Logic](#bitwise-logic)
    * [Bitshifting Left and Right](#bitshifting-left-and-right)


## Install

Download the REPO, then enter the repo and run:

```bash
make
```

This will build 2 files. `calc` and `calc-test`.

`calc` is the actual calculator application while `calc-test` is an application
that runs sum tests that are defined in `tests/test.c`.

## Run Tests

You can either run the `calc-test` application which will run all the tests, or
you can run:

```bash
make test
```

which just does the same thing but also runs valgrind to check for memory leaks.

## Usage

Run the calculator with:

```bash
./calc
```

Operate as a normal RPN Calculator.

Alternatively, there is an expression command (`e`) command where you can type
out an RPN calculation on one line with all the numbers and operators separated
by spaces.

For Example: `e 2 6 + 4 * 2 / 4 +` which would equate to `20`.

### Entering Hex, Octal, or Binary Numbers

You will see later on in the [Change Numeric Base](#change-numeric-base)
section, that we are able to change the numeric base that the numbers are
displayed in.

Here I will explain how to actually enter numbers in other bases.

#### Decimal

We will start easy. To enter a number in base 10 (decimal), just enter the
number as normal.

#### Hexadecimal

To enter a Hex number, you must prefix the number with a `0x` or `0X`. For
example, if I wanted to enter the hex number `4f`, I would type `0x4f` and press
enter.

The calculator will take the number, recognize it as hex, and it will display
the number in whatever numeric base you have chosen for the calculator (by
default the calculator is in decimal, so if you enter `0x4f` without changing
the base, you will actually see `79.000000` come onto the stack, since `4f` in
hexadecimal is `79` in decimal).

#### Octal

To enter an Octal number, you must prefix the number with a `0`. For
example, if I wanted to enter the octal number `25`, I would type `025` and
press enter.

The calculator will take the number, recognize it as octal, and it will display
the number in whatever numeric base you have chosen for the calculator (by
default the calculator is in decimal, so if you enter `025` without changing the
base, you will actually see `21.000000` come onto the stack, since `25` in
octal is `21` in decimal).

#### Binary

To enter a Binary number, you must prefix the number with a `0b` or `0B`. For
example, if I wanted to enter the binary number `1010101`, I would type
`0b1010101` and press enter.

The calculator will take the number, recognize it as binary, and it will display
the number in whatever numeric base you have chosen for the calculator (by
default the calculator is in decimal, so if you enter `0b1010101` without
changing the base, you will actually see `85.000000` come onto the stack, since
`1010101` in octal is `85` in decimal).

## Supported Operations

### Stack Manipulations

Stack manipulations are non math related operations that affect the state of the
stack.

#### Duplicate Stack Element

* `\n`:
  * Entering just a blank input into the calculator duplicates the last number
    that was entered to the stack.

> ##### Example:
>
> Starting with this:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> ===============================================================
> ```
>
> We would get this if we did a duplication:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> 2:  10.000000
> ===============================================================
> ```

#### Drop Element From the Stack

The drop commands removes entries from the stack.

*  `d`:
  * These drop commands all drop the last entry on the stack.

> ##### Example:
>
> Starting with this:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> 2:  20.000000
> 3:  30.000000
> 4:  40.000000
> ===============================================================
> ```
>
> We would get this if we did a `drop` command:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> 2:  20.000000
> 3:  30.000000
> ===============================================================
> ```

#### Swap Stack Elements

The swap commands swap stack entries with one another.

* `s`:
  * Swaps the last stack entry with the second to last stack entry.

> ##### Example:
>
> Starting with this:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> 2:  20.000000
> 3:  30.000000
> 4:  40.000000
> ===============================================================
> ```
>
> This is what we get if we perform a `swap`:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> 2:  20.000000
> 3:  40.000000
> 4:  30.000000
> ===============================================================
> ```

#### Clear the Stack

The clear command clears the whole stack or a defined part of it.

* `<escape>`:
  * Pressing the escape button clears the WHOLE stack.

> ##### Example:
>
> Starting with this:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> 2:  20.000000
> 3:  30.000000
> 4:  40.000000
> ===============================================================
> ```
>
> This is what we get if we perform a `clear` operation:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> ===============================================================
> ```

### Calculator Settings

These are settings that can be made to the Calculator to change how it behaves
or displays information.

#### Change Angle Mode

These settings change the angle that the calculator assumes for the Trig
functions.

* `ctrl+e`, `ctrl+r`:
  * These commands change the mode of the calculator to Degrees or Radians
    respectively.

> ##### Example:
>
> NOTE: To see how the different modes actually work with Operations that use
> angles, see [Trigonometric Functions](#trigonometric-functions). These
> examples won't show the use of degrees vs radians, but just shows how to
> change them with the command.
>
> Starting with this:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> ===============================================================
> ```
>
> This is what we get if we use the `degree` command:
>
> ```
> ===============================================================
>       +---+
>  RAD  |DEG|
>       +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> ===============================================================
> ```
>
> Performing the `radian` command then takes us back to:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> ===============================================================
> ```

#### Change Numeric Base

These settings change the numeric base that the calculator uses to DISPLAY
numeric values. It does NOT affect how numbers are interpreted. To find out how
to enter hex, octal, or binary numbers into the calculator, see [Usage](#usage).

* `ctrl+h`, `ctrl+d`, `ctrl+o`, `ctrl+b`:
  * These commands change the mode of the calculator to hexadecimal, decimal,
    octal, and binary respectively.

> ##### Example:
>
> NOTE: that the decimal part of a number is not displayed in any mode other
> than decimal. So if you enter the number `5.5` and then change to hex mode, it
> will display as just `5`. Please note that this is ONLY displayed information
> and that the fractional part of the number is still there, it is just not
> displayed. This is the way that C handles different bases (ie. as integers).
> Also, because they are displayed as integers, displaying numbers in a base
> other than decimal could result in a number rolling over because it is handled
> as an integer which is a much smaller datatype than what the calculator uses
> for decimal numbers. Again, just because it is displayed as rolled over, it is
> not, and performing math on it or converting it back to decimal will work
> fine (unless it has rolled over in decimal mode).
>
> Starting with this:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>       +---+
>  HEX  |DEC|  OCT   BIN
>       +---+
>
> 1:  10.000000
> 2:  20.000000
> 3:  30.000000
> 4:  40.000000
> 5:  50.000000
> 6:  6.000000
> ===============================================================
> ```
>
> Note that currently it is in decimal mode which is the standard setting.
>
> Now we will change to hex mode:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
> +---+
> |HEX|  DEC   OCT   BIN
> +---+
>
> 1:  a
> 2:  14
> 3:  1e
> 4:  28
> 5:  32
> 6:  6
> ===============================================================
> ```
>
> Notice that the setting at the top has moved to `HEX`. Also, all the numbers
> on the stack have been converted to hexadecmial.
>
> Now to change to octal:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>             +---+
>  HEX   DEC  |OCT|  BIN
>             +---+
>
> 1:  12
> 2:  24
> 3:  36
> 4:  50
> 5:  62
> 6:  6
> ===============================================================
> ```
>
> And finally, binary:
>
> ```
> ===============================================================
> +---+
> |RAD|  DEG
> +---+
>                   +---+
>  HEX   DEC   OCT  |BIN|
>                   +---+
>
> 1:  1010
> 2:  10100
> 3:  11110
> 4:  101000
> 5:  110010
> 6:  110
> ===============================================================
> ```

### Math Operations

Features that perform mathematical operations on the numbers on the stack.

#### Basic Arithmetic
#### Exponents and Radicals
#### Absolute Values
#### Reciprocation
#### Trigonometric Functions
#### Logarithmic Functions
#### Sums of Groups of Numbers
#### Operations on Specified Stack Entries
#### Factorial
#### Fibonacci
#### Random Number Generator

### Mathematical Constants

#### π
#### e

### Bitwise Operations

#### Bitwise Logic
#### Bitshifting Left and Right
