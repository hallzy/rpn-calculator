# RPN Calculator

RPN Calculator for the terminal.

* Currently supports a stack size of 128
* Numerous mathematical functions

## Table of Contents

* [Install](#install)
* [Run Tests](#run-tests)
* [Usage](#usage)
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

Operate as a normal RPN Calcualtor.

NOTE: This calculator will require the `enter` key to be pressed in order to
register anything. Otherwise it won't know when you are done writing your
command.

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

* `drop`, `d`:
  * These drop commands all drop the last entry on the stack.
* `dropx`, `dx`:
  * These drop commands all drop the stack entry on line x (where x is the last
    stack entry)

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
> We would get this if we did a regular drop command (`d`):
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
>
> If we now entered a `2` onto the stack:
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
> 4:  2.000000
> ===============================================================
> ```
>
> and do a `dx` command, we would be removing the 2nd value in the stack and get
> this:
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
> 2:  30.000000
> ===============================================================
> ```

#### Swap Stack Elements

The swap commands swap stack entries with one another.

* `swap`, `s`:
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
> This is what we get if we perform a `s` operation:
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

* `clear`, `c`:
  * Clears the WHOLE stack.
* `clearx`, `cx`:
  * Clears all stack entries from the bottom of the stack up to (but not
    including) the stack entry numbered by x (where x is the last entry on the
stack)

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
> This is what we get if we perform a `c` operation:
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
> If we then start with this:
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
> 5:  2.000000
> ===============================================================
> ```
>
> Then this is what we get if we perform a `cx` operation (note that the 2 at line
> 5 is the x argument for `cx`):
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
> ===============================================================
> ```

### Calculator Settings

These are settings that can be made to the Calculator to change how it behaves
or displays information.

#### Change Angle Mode
#### Change Numeric Base

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

### Mathematical Constants

#### π
#### e

### Bitwise Operations

#### Bitwise Logic
#### Bitshifting Left and Right
