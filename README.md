# Deviantz Rulez Utility pack

## What is this?
In this project I want to collect all the little C++ things that I made for myself but thought would be useful for others.

## List of goodies
- String functions (join, split)
- DateTime functions (datetime to string, current time to string timestamps)
- WaitUntil
- Sizes (KB, MB, GB, TB calculation and string conversion)
- Threadpool implementation
- Log implementation
  
## Get started
### Platform

I wrote these codes under an Ubuntu Linux 24.02, but they should be usable any linux distro.
The compiler was GCC 13, but you can use whatever you like (Clang, GCC...)
### Usage

Basically, I wrote everything directly in singleheader hpp files, so essentially if you copy them, they become usable immediately.
I attached a vscode configuration to the project, which contains the basic settings, but you can easily rewrite this yourself.
In principle, most modules can be used on their own, but there are some that can be built on top of each other.
Such e.g. the log module, which also uses the common utilities datetime header for timestamps.

### Help
I've commented on almost every line (according to the doxygen standard), so if you can read, it's relatively easy to figure out what's doing what in the code. I dare to recommend it if you are a beginner in C++ programming.

## Maintaining and contribution

I would like to collect as many of these small C++ things as possible here, but I don't always have time to maintain them or fix them. I'll fix things accordingly when I get there.

You can freely use the codes, take them apart, put them together, and use them for sales purposes, but I only ask that you mark my name in the project (or do not remove it from the description of the header files). I assume no responsibility for risks or errors arising from use.
