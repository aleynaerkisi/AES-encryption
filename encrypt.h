#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h>
using namespace std;


const int round_num = 10; //Number of Rounds
typedef bitset<8> byte; //message 16*8 =128bit
//typedef bitset<32> word; //round key 4*32=128bit

int m = 0;
int ascii[4][4]; //ascii array that holds decimal values of the message... bunu s-box için tekrar dönüþtürmeye gerek kalmadan kullan. s0,0 ascii 0,0 þeklinde denk gelen sayýyý s-boxtan al.
//byte bin[4][4]; //binary values array 
byte subs_bytes[4][4]; 
byte round_sub_bytes[4][4];
byte roundKey[4][4];
char cipher[16];

//s_box that is used in step 1 of encyption
byte S_Box[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}
};

byte Rcon[10] = { 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
                 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000 };

int mix_array[4][4] = {
    {2,3,1,1},
    {1,2,3,1},
    {1,1,2,3},
    {3,1,1,2}
};

//because they were char and i need int
int hexToInt(char a)
{
    int s_box_value=0;
    switch (a)
    {
    case '0':
        s_box_value = 0;
        break;
    case '1':
        s_box_value = 1;
        break;
    case '2':
        s_box_value = 2;
        break;
    case '3':
        s_box_value = 3;
        break;
    case '4':
        s_box_value = 4;
        break;
    case '5':
        s_box_value = 5;
        break;
    case '6':
        s_box_value = 6;
        break;
    case '7':
        s_box_value = 7;
        break;
    case '8':
        s_box_value = 8;
        break;
    case '9':
        s_box_value = 9;
        break;
    case 'A':
        s_box_value = 10;
        break;
    case 'B':
        s_box_value = 11;
        break;
    case 'C':
        s_box_value = 12;
        break;
    case 'D':
        s_box_value = 13;
        break;
    case 'E':
        s_box_value = 14;
        break;
    case 'F':
        s_box_value = 15;
        break;
    }

    return s_box_value;
}

//text to ascii decimal
void to_Ascii(string s)
{
	//int k = 0;
	//convertion to decimal
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ascii[i][j] = s[i*4+j];
           // cout << ascii[i][j]<< " ";
		}
	}
    


}

//opposite of the to_Ascii funciton
void to_Ascii_to_char()
{
    int a;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            
            a = static_cast<char>(ascii[i][j]);
            //cout << "First values" << a << " ";
            /*if (a < 0)
            {
                a= a * (-1);
                cout << "After negative values are turned into positive" << a << endl << endl;
            }
            
            if (a > 90)
            {
                while(a>90)
                    a = a % 26 + 65;
            
            
            }

            else if (a < 65)
            {
                a = a % 26 + 65;
            }*/
            
            //cout << "After modulo applied"<< a << endl;
            cipher[i*4+j] = a;
            //cout << cipher[i * 4 + j];
            
        }
    }
}

/*
	main içinde
	string a="I.want.to.finish";
	to_Ascii(a);
*/

//convert the binary values to decimal ascii values
void byte_to_ascii()
{
    byte p;
    int x;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            
            p = subs_bytes[i][j];
            x = p[7] + (p[6] * 2) + (p[5] * 4) + (p[4] * 8) + (p[3]*16) + (p[2] * 32) + (p[1] * 64) + (p[0] * 128);
            
            ascii[i][j] = x;

        }

    }
}

//opposite of byte_to_ascii function
void ascii_to_byte(int arr[4][4])
{
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            byte s(arr[i][j]);
            subs_bytes[i][j] = s;
            
        }
        
    }
}



void substituteBytes()
{
  //converts all the decimal values to binary first

    //for (int i = 0; i < 4; i++)
    //{
    //    for (int j = 0; j < 4; j++)
    //    {
    //        byte s(arr[i][j]);
    //        subs_bytes[i][j] = s;
    //        //cout << subs_bytes[i][j] << " ";
    //    }
    //    //cout << endl;
    //}
    //cout << endl << endl;
    //cout << subs_bytes[0][0];
    //cout << subs_bytes[0][0][0]; //son bit(tam ters veriyor)

    
    //now divide each part to 4bit and calculate the decimal value of the 4bit only part
    //eg 01001001 => 0100-1001 => 4-9 => s-box [4][9]
    byte p;
    int x, y; 
    for (int i = 0; i < 4; i++)
    {
        
        for (int j = 0; j < 4; j++)
        {
            p = subs_bytes[i][j];
            x = p[7] + (p[6] * 2) + (p[5] * 4) + (p[4] * 8);
            y = p[3] + (p[2] * 2) + (p[1] * 4) + (p[0] * 8);
            subs_bytes[i][j] = S_Box[x][y]; 
        }

    }
        
}

void shiftRows()
{
    //move on from here subs_bytes
    //first row no change
    
    
    //second row 1 shift 

    byte temp0,temp1,temp2,temp3;
    //swap s10 to the place of s12
    //swap s11 to the place of s10
    //swap s12 to the place of s11
    //swap s13 to the place of s13

    temp0= subs_bytes[1][0];
    temp1= subs_bytes[1][1];
    temp2= subs_bytes[1][2];
    temp3 = subs_bytes[1][3];

    subs_bytes[1][0] = temp1;
    subs_bytes[1][1] = temp2;
    subs_bytes[1][2] = temp3;
    subs_bytes[1][3] = temp0;

    //second row shift over
    //third row shift

    //swap s20 to the place of s22
    //swap s21 to the place of s23
    //swap s22 to the place of s20
    //swap s23 to the place of s21

    temp0 = subs_bytes[2][0];
    temp1 = subs_bytes[2][1];
    temp2 = subs_bytes[2][2];
    temp3 = subs_bytes[2][3];

    subs_bytes[2][0] = temp2;
    subs_bytes[2][1] = temp3;
    subs_bytes[2][2] = temp0;
    subs_bytes[2][3] = temp1;

    //third row shift over
    //forth row shift

    //swap s30 to the place of s31 
    //swap s31 to the place of s32
    //swap s32 to the place of s33
    //swap s33 to the place of s30

    temp0 = subs_bytes[3][0];
    temp1 = subs_bytes[3][1];
    temp2 = subs_bytes[3][2];
    temp3 = subs_bytes[3][3];

    subs_bytes[3][0] = temp3;
    subs_bytes[3][1] = temp0;
    subs_bytes[3][2] = temp1;
    subs_bytes[3][3] = temp2;

}



byte GFMul(byte a, byte b) {
    byte p = 0;
    byte hi_bit_set;
    for (int counter = 0; counter < 8; counter++) {
        if ((b & byte(1)) != 0) {
            p ^= a;
        }
        hi_bit_set = (byte)(a & byte(0x80));
        a <<= 1;
        if (hi_bit_set != 0) {
            a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */
        }
        b >>= 1;
    }
    return p;
}

void mixColumns()
{
    int k;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            k = 0;
            subs_bytes[i][j] = GFMul(subs_bytes[k][j], mix_array[j][k++]);
            subs_bytes[i][j] = subs_bytes[i][j] ^ GFMul(subs_bytes[k][j] , mix_array[j][k++]);
            subs_bytes[i][j] = subs_bytes[i][j] ^ GFMul(subs_bytes[k][j] , mix_array[j][k++]);
            subs_bytes[i][j] = subs_bytes[i][j] ^ GFMul(subs_bytes[k][j] , mix_array[j][k]);
            //cout << "from mix Columns ";
            //cout << subs_bytes[i][j]<< " ";
            
            
        }
        //cout << endl;

    }

}


void RoundKeyCreate()
{
    byte p;
    int x, y;
    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            p = subs_bytes[i][j];
            x = p[7] + (p[6] * 2) + (p[5] * 4) + (p[4] * 8);
            y = p[3] + (p[2] * 2) + (p[1] * 4) + (p[0] * 8);
            round_sub_bytes[i][j] = S_Box[x][y];
        }

    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            roundKey[j][i] = GFMul(subs_bytes[j][i], round_sub_bytes[j][i]);
            roundKey[j][i] = GFMul(subs_bytes[j][i], Rcon[m]);
        }
    }

}


void AddRoundKey()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            subs_bytes[i][j] = GFMul(subs_bytes[j][i], round_sub_bytes[j][i]);
            
        }
    }
}