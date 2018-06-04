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

To learn more about how to write in SunnyLang, check out the [wiki](https://github.com/evanmarcey/SunnyLang/wiki/SunnyLang).

### Features
The language currently supports:
 - Variable declaration and assignment for integer, float and boolean variables
  - String variables are planned, but not yet supported
 - If/Else logic
 - For/While loop control flow
 - A whole mess of operators
 - Well that's really it.
 
Planned features:
  - User-Defined Function implementation
  - User-Defined Class implementation
  - Additional built-in variables (i.e. arrays)
  - Additional built-in functions
  - Memory management
  
### Source Code

The SunnyLang interpreter is written and compiled in C.

All of the code for the interpreter is in [src](https://github.com/evanmarcey/SunnyLang/tree/master/src).

Sunny.c is the main source file, which kicks off the entire process, and Tokenizer.c contains the majority of the code for tokenizing and evaluating a line of SunnyLang.

The user-defined structs are in [struct](https://github.com/evanmarcey/SunnyLang/tree/master/src/struct), and similarly all utilities are contained in [util](https://github.com/evanmarcey/SunnyLang/tree/master/src/utils).


