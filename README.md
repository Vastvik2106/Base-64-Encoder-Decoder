# Vortex64: Base 64 Encoder/Decoder in c++
Implemented Base64 encoding and decoding entirely from first principles in C++, manually transforming raw binary streams into 6-bit Base64 representations and reconstructing the original bytes, with binary/image support and a custom CLI without external encoding libraries.

## Vortex64: Description
Vortex64 is a pure C++ implementation of the Base64 encoding and decoding pipeline, built from first principles using manual bit-level transformations to convert arbitrary binary streams into 6-bit Base64 representations and reconstruct the original data, with support for binary and image files through a custom CLI.


## Features
- Manual bit-level binary-to-Base64 conversion
- Manual Base64-to-binary reconstruction
- Standard C++ implementation using STL
- Support for arbitrary binary data
- Image file encoding
- Image file decoding
- Support for PNG/JPEG and other binary file types
- Decode Base64 data back into files
- No external Base64/encoding libraries

## How it works
### Encoding (both images and texts)
The encoder begins by reading the input as a raw binary stream, allowing Vortex64 to operate on arbitrary files including text, images, and other binary data without interpreting their contents at the application level.

Each byte is represented as an 8-bit binary sequence. The resulting bitstream is then processed in groups of 6 bits. Since a 6-bit value can represent 2^6=64 distinct values, each 6-bit group is mapped to one character from the Base64 alphabet. The fundamental transformation is therefore [3 bytes → 24 bits → 4 × 6-bit groups → 4 Base64 characters].

Each resulting 6-bit integer is used as an index into the Base64 alphabet, producing the encoded representation.

When the input length is not divisible by three, the final incomplete group is padded with zero bits to complete the required 6-bit representation. Base64 additionally uses = characters as structural padding so that the final encoded output maintains a length divisible by four.

Thus, the encoder performs a deterministic transformation [Raw Binary Data → 8-bit bytes → Bit-level decomposition → 6-bit indices → Base64 alphabet mapping → Base64 representation]

## Decoding
The decoder reverses this transformation.
Each Base64 character is first mapped back to its corresponding 6-bit numerical value using the Base64 alphabet. These 6-bit values are then reconstructed into the original byte stream.Padding characters are interpreted according to the number of meaningful bytes represented by the final Base64 block, ensuring that only the original data is reconstructed. The complete decoding pipeline is therefore Base64 [Representation → Alphabet lookup → 6-bit values → Bit-level reconstruction → 8-bit bytes → Original Binary Data].

Because Vortex64 operates on raw bytes rather than characters or image pixels, the same encoding and decoding mechanism can be applied to essentially any binary file. An image is therefore not treated as an image internally it is treated as its underlying byte sequence. The implementation consequently demonstrates the complete Base64 transformation at the byte and bit level, rather than abstracting the process behind a pre-existing encoding library.


>					Vortex64
>        ┌──────────────┴──────────────┐
>        ↓                             ↓
>   Binary → Base64                Base64 → Binary
>        │                             │
>        ↓                             ↓
>   Any byte stream              Original bytes
>        │                             │
>        └──────────────┬──────────────┘
>			           ↓
>             Text / Images / Files

## How to use it
1) Clone the repository:
> git clone https://github.com/Vastvik2106/Base-64-Encoder-Decoder.git
> cd Base-64-Encoder-Decoder

2) Compile the program:
Bash
> g++ -std=c++17 main.cpp -o Vortex64

3) Run the program:
> ./Vortex64

