# SunnyLang

Hello! Evan Marcey here. Local business owner and computer enthusiast!

Is your computer constantly stomping around, driving you crazy?

Is your computer clawing at your furnitures?

Think there's no answer?! You're so stupid!

SunnyLang.

Finally, there's an elegant comfortable language for programmers.

Come on down to Paddy's Pub! We're the home of the original SunnyLang!

Meow!

## Overview

SunnyLang is a statically-typed interpreted language where all of the commands are quotes from _It's Always Sunny in Philadelphia._ SunnyLang is parsed and evaluated line-by-line, so any declarations must occur prior to being called in the code.

It's also definitely not finished yet. I just wanted a place to back it up.

### Features
The language currently supports:
 - Variable declaration and assignment for integer, float and boolean variables
  - String variables are planned, but not yet supported
 - If/Else logic
 - Well that's really it.
 
Planned features:
  - And/Or implemention
  - User-Defined Function implementation
  - User-Defined Class implementation
  - Additional built-in variables (i.e. arrays)
  - Additional built-in functions
  - For/While loop control flow
  - Memory management
  
### Syntax

#### Variables

Variables must be declared with an accepted type in the following format:

```
Declare variable {type}
// or
Declare variable {type} = {expression}
```
which is translated into SunnyLang as:

```
JoinTheGang variable {type}
// or
JoinTheGang variable {type} MilkSteak {expression}
```

The current acceptable types are:

SunnyLang Name | Type
--- | ---
Dennis | Int
Mac | float
Dee | boolean
Charlie | string

Notes:
 - strings may be declared, but the evaluation of strings is not yet implemented, so using them in an expression will throw an error
 - boolean variables are much the same as in C, where True = 1 and False = 0. 
    - As such, boolean variables can be used in any mathematical expression

#### Expression Evaluation

The evaluator expects an infix expression and evaluates as such. 

Order of operations is much the same as in a math class, except that some additional handling is invoked so that equality signs can be used. Equality signs evaluate the entire left-hand side of an expression (up to a '('), store the result of the left-hand side, then continue evaluating the entirety of the right-hand side (up to a ')') before comparing the results.

And/Or handling will follow much the same pattern, but with a higher precedence than equality signs.
  
### Source Code

The SunnyLang interpreter is written and compiled in C.

All of the code for the interpreter is in [src](https://github.com/evanmarcey/SunnyLang/tree/master/src).

Sunny.c is the main source file, which kicks off the entire process, and Tokenizer.c contains the majority of the code for tokenizing and evaluating a line of SunnyLang.

The user-defined structs are in [struct](https://github.com/evanmarcey/SunnyLang/tree/master/src/struct), and similarly all utilities are contained in [util](https://github.com/evanmarcey/SunnyLang/tree/master/src/utils).

## Examples
