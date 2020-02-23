---
Hamming Code generator and single-error finding program
---

Installation instructions:
a) mkdir build
b) cd build
c) cmake ..
d) make
e) ./ham

Features:
1) Generate hamming code for a n bits (n <= 120) message. First, enter your message size in
bits, then write (without using spaces or underscores or any other characters) your message
in binary.
2) Check and find a single error (after all Hamming is a single-error correction code). You
just type the size of the Hamming-encoded message and then the message itself and the
program will check if there is an error. If there is, it will correct it and point it out.

(If you need a tutorial on Hamming code generation and error finding, check this [video](https://www.youtube.com/watch?v=373FUw-2U2k)).
