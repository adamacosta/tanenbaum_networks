#include <stdio.h>
#include <string.h>

char *MakeCRC(char *BitString)
   {
   static char Res[8];                                 // CRC Result
   char CRC[7];
   int  i;
   char DoInvert;
   
   for (i=0; i<7; ++i)  CRC[i] = 0;                    // Init before calculation
   
   for (i=0; i<strlen(BitString); ++i)
      {
      DoInvert = ('1'==BitString[i]) ^ CRC[6];         // XOR required?

      CRC[6] = CRC[5] ^ DoInvert;
      CRC[5] = CRC[4];
      CRC[4] = CRC[3] ^ DoInvert;
      CRC[3] = CRC[2] ^ DoInvert;
      CRC[2] = CRC[1];
      CRC[1] = CRC[0];
      CRC[0] = DoInvert;
      }
      
   for (i=0; i<7; ++i)  Res[6-i] = CRC[i] ? '1' : '0'; // Convert binary to ASCII
   Res[7] = 0;                                         // Set string terminator

   return(Res);
   }

// A simple test driver:

int main()
   {
   char *Data, *Result;                                       // Declare two strings

   Data = "1101000101000111";
   Result = MakeCRC(Data);                                    // Calculate CRC
   
   printf("CRC of [%s] is [%s] with P=[11011000]\n", Data, Result);
   
   return(0);
   }