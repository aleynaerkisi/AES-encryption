#include "encrypt.h";
//#define N 4


int main()
{

    string msg = "I.want.to.finish";
   // string msg = "abcabcabcabcabca";
    cout << "message to be encrypted is this : " << msg << endl << endl;

    //message is converted to integer values  
    to_Ascii(msg);


    //cout << "message converted in integer and 4x4 matrix is this : " << endl << endl;
    /*for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << ascii[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/

    //cout << "message in hex format :" << endl << endl;

    ascii_to_byte(ascii);

    substituteBytes();  //Step1 --converts the values to 8bit binary format and use s-box too


   


    shiftRows(); //step2
    /*cout << endl << "after row shift " << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << subs_bytes[i][j] << " ";
        }

        cout << endl;
    }*/

    //mix columns starts here
    
    
    
    //cout << endl << endl;
    
    mixColumns(); //step3

    //mix columns ends here

   
   
    //addround key
     
    RoundKeyCreate();

    
    //1st round over

   
    AddRoundKey();
    m++; //round increase

    //next 8 steps

    for (int o = 0; o < 8; o++)
    {
        substituteBytes();
        shiftRows();
        mixColumns();
        RoundKeyCreate();
        AddRoundKey();
        m++;
    }
    
    /*for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << round_sub_bytes[i][j] << " ";
        cout << endl;
    }*/

    //last round starts here

    substituteBytes();
    shiftRows();
    RoundKeyCreate();
    AddRoundKey();

    cout << endl;

    /*cout << "After 10 rounds: " << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << subs_bytes[i][j] << " ";
        cout << endl;
    }*/

    //last step is to converrt the byte matrix to decimal and then to string

    byte_to_ascii();
    to_Ascii_to_char();



    cout << "Cipher message is this: " << endl;
    for (int i = 0; i < 16; i++)
        cout << cipher[i];

    cout << endl;

    

    return 0;

}