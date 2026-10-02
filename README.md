# DNA Sequence Analyzer

A C++ command-line application for working with DNA sequences. The program provides a menu-driven toolkit for generating sequences, searching patterns, building graphs, simulating replication, transcribing and translating molecules, performing transformations, comparing sequences, and sorting sequence collections.

## Features

The analyzer includes the following capabilities:

- Generate random DNA sequences with a configurable length and seed
- Search for patterns in a DNA sequence using KMP substring search
- Build and traverse a De Bruijn graph
- Replicate a DNA strand into its complementary pair
- Transcribe DNA to RNA
- Translate RNA into a protein sequence starting at AUG and stopping at a stop codon
- Transform DNA by complementing, reversing, reversing complement, substituting, inserting, or deleting bases
- Compare two DNA sequences by equality, similarity, mismatches, and Hamming distance
- Sort multiple sequences by length using several algorithms
- Run the built-in automated test suite

## Project structure

- src/: implementation files for the DNA utilities and CLI entry point
- include/: headers for the public API
- tests/: project test data and test suite
- build/: generated CMake build output

## Requirements

- CMake 3.16 or newer
- C++17-compatible compiler
- Make or an equivalent generator for your platform

## Build

From the project root:

```powershell
cmake -S . -B build
cmake --build build
```

This produces the executable files in the build directory:

- build/dna_analyzer.exe
- build/dna_tests.exe

## Run the app

You can run the analyzer from PowerShell:

```powershell
.\build\dna_analyzer.exe
```

If Windows blocks the executable because it was downloaded from another source, unblock it first:

```powershell
Unblock-File -Path .\build\dna_analyzer.exe
.\build\dna_analyzer.exe
```

The program presents the following menu:

1. Generate Random DNA Sequence
2. Search DNA Sequence
3. Build De Bruijn Graph
4. Replicate DNA
5. Transcribe DNA to RNA
6. Translate RNA to Protein
7. Transform DNA Sequence
8. Compare Two Sequences
9. Sort Sequences by Length
10. Run Test Cases
0. Exit

## Example usage

- Choose option 1 to create a random DNA sequence
- Choose option 2 to find a motif in a sequence
- Choose option 3 to build a De Bruijn graph from a string
- Choose option 5 to convert DNA to RNA using the template-strand rules
- Choose option 6 to translate AUG-based RNA into a protein string
- Choose option 10 to execute the included test suite

## Run tests

```powershell
.\build\dna_tests.exe
```