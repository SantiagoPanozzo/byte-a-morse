// Morse binary protocol
// ---------------------
// Represent a single letter with 8 bits in the morse code format!
// Also supports lowercase and uppercase! And spaces!
// All of this to get a whopping like 53 characters per byte.
// Is this CPU-efficient? No.
// Is this storage-efficient? No.
// Is there any technical advantage over ASCII? Nah.
// Why? Why not.
// Ok, the cool thing is that if you know morse code you can write letters in binary with this,
// but yeah it's pretty useless otherwise /shrug
//
// TODO:
// - Optimize functions
// - Make interactive (shitty CLI)

#include <stdio.h>

char lookup1(char input)
{
  if (input == 0b1) {
    return 'e';
  }
  return 't';
}

char lookup2(char input)
{
  switch (input) {
    case 0b10:
      return 'a';
    case 0b11:
      return 'i';
    case 0b00:
      return 'm';
    case 0b01:
      return 'n';
    default:
      return ' ';
  }
}

char lookup3(char input){
  switch (input) {
    case 0b011:
      return 'd';
    case 0b001:
      return 'g';
    case 0b010:
      return 'k';
    case 0b000:
      return 'o';
    case 0b101:
      return 'r';
    case 0b111:
      return 's';
    case 0b110:
      return 'u';
    case 0b100:
      return 'w';
    default:
      return 'x';
  }
}

char lookup4(char input){
  switch (input) {
    case 0b0111:
      return 'b';
    case 0b0101:
      return 'c';
    case 0b1101:
      return 'f';
    case 0b1111:
      return 'h';
    case 0b1000:
      return 'j';
    case 0b1011:
      return 'l';
    case 0b1001:
      return 'p';
    case 0b0010:
      return 'q';
    case 0b1110:
      return 'v';
    case 0b0110:
      return 'x';
    case 0b0100:
      return 'y';
    case 0b0011:
      return 'z';
    default:
      return ' ';
  }
}



// Should receive something like '0000 0111', since only the last 4 bits will contain a value
char decode(char input)
{
  const char siz = input & 0b01110000;
  const char val = input & 0b00001111;
  char res;
  switch(siz){
    case 0b00010000:
      // printf("size 1\n");
      res = lookup1(val);
      break;
    case 0b00100000:
      // printf("size 2\n");
      res = lookup2(val);
      break;
    case 0b00110000:
      // printf("size 3\n");
      res = lookup3(val);
      break;
    case 0b01000000:
      // printf("size 4\n");
      res = lookup4(val);
      break;
    default:
      // printf("size ?\n");
      return ' ';
  }
  if (input & (1 << 7))
    return res - 32;
  return res;
}

int main(int argc, char *argv[])
{
  // IsUpper  Size  Code - Result
  // 1        010   0010 - A
  // 0        010   0010 - a
  // 1        100   0111 - B
  //
  // size 0 and anything else that fails is a space ' '
  
  // Uppercase A
  printf("%c\n", decode(0b10100010));
  
  // Lowercase A
  printf("%c\n", decode(0b00100010));

  // Uppercase B
  printf("%c\n", decode(0b11000111));
  return 0;
}
