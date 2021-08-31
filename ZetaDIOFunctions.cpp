//=============================================================================
// (c) Copyright 2021 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: ZetaDIOFunctions.c  v8.3.0
//
// Depedency :	Universal Driver version 8.3.1
//				DSCUD.H - Include file.
//				
//				LIBDSCUD-8.3.1.a	- Library file for Linux 3.2-4.8
//						
//				DSCUD.LIB	- Static library file for Windows 
//						( USE VC++ 6.0 or Visual Studio 2008 )
//				
//
// ZetaDIOFunctions.c  v8.3.0
// Desc: Writes and reads from Digital I/O port
//============================================================================
#include <iostream>
#include <string>
#include <regex>
#include <sstream>

#include "Parser.hpp"

#include "DSCUD_demo_def.h"
#include "Zeta.h"

using namespace std;

class errorCheck
{
	private:
		// globals
		ERRPARAMS errorParams; // structure for returning error code and error string
	public:
		errorCheck()
		{
			dscGetLastError ( &errorParams );
			printf ( "dscInit error: %s %s\n", dscGetErrorString ( errorParams.ErrCode ), errorParams.errstring );
			cout<< "dscInit error: "<< dscGetErrorString ( errorParams.ErrCode ) << errorParams.errstring << endl;
		}
};

constexpr uint8_t DIOPORT_MAX {4};
//DIO Port No
constexpr uint8_t DIOPORT_A {0};
constexpr uint8_t DIOPORT_B {1};
constexpr uint8_t DIOPORT_C {2};
constexpr uint8_t DIOPORT_D {3};


constexpr uint8_t  READ_BIT				           {1};
constexpr uint8_t  WRITE_BIT         	   	   	   {2};
constexpr uint8_t  LOOP_BACK_TEST				   {3};


// var declarations
DSCB dscb = 0; // handle used to refer to the board
DSCCBP dsccbp; // structure containing board settings
int portConfig[4];//used to store the port directions
DSCCB dsccb;

class byte
{
	public:
		byte();
		uint8_t readBitsDIOPort(uint8_t localport,uint8_t localBitNumber);
		void writeBitDIOPort(uint8_t localport,uint8_t localBitNumber,uint8_t localBitValue);
		void DIOPortLoopbackTest();
		void enable(uint8_t localport,uint8_t localBitNumber);
		void disable(uint8_t localport,uint8_t localBitNumber);
		Parser mParser;
	private:
		//new variables
		char input_buffer[20];
};
byte::byte()
{
}

//=============================================================================
// Name: readAllBitsDIOPort()
// Desc: Read all bits  from the selected port's  register.
// Parameters:void
// Return: void
//=============================================================================
uint8_t byte::readBitsDIOPort(uint8_t localport,uint8_t localBitNumber)
{
	BYTE* config = NULL;
	BYTE enable = 0;
	BYTE port = 0;
	BYTE Dir = 0;
	BYTE input_byte = 0;
	BYTE bit = 0;

	config = (BYTE*)malloc(sizeof(BYTE)*3);

	config[0] = port;
	config[1] = enable;
	config[2] = Dir;

	
	if(dscDIOSetConfig(dscb,config)!= DE_NONE)
	{
		errorCheck errorChecker();
	}

	port = 1;
	config[0] = port;

	if(dscDIOSetConfig(dscb,config)!= DE_NONE)
	{
		errorCheck errorChecker();
	}

	port = 2;
	config[0] = port;

	if(dscDIOSetConfig(dscb,config)!= DE_NONE)
	{
		errorCheck errorChecker();
	}

	port = 3;
	config[0] = port;

	if(dscDIOSetConfig(dscb,config)!= DE_NONE)
	{
		errorCheck errorChecker();
	}

	
	if(localport == 0 || localport == 1 || localport == 2)
	{
		//bit = (BYTE) localBitNumber;
	}
	else if(localport == 3)
	{
		if(localBitNumber >=3)
		{
			cout << "Bit number shall be less than 3! \n";
		}
		//bit = (BYTE) intBuff - 5;
		//bit = (BYTE) localBitNumber;
	}

	if ( (dscDIOInputBit ( dscb, localport, localBitNumber, &input_byte ) != DE_NONE) )
	{
		errorCheck errorChecker();
	}

	dscSleep(1000);

	return input_byte;
}

//=============================================================================
// Name: writeBitDIOPort()
// Desc: Program a port A-D by sending a digital value to the selected
// 	  port's bit register.
// Parameters:void
// Return: void
//=============================================================================
void byte::writeBitDIOPort(uint8_t localport,uint8_t localBitNumber,uint8_t localBitValue)
{
	BYTE* config = NULL;
	int enable = 0;
	int Dir = 1;
	

	if(localport==0 || localport==1)
	{
		enable = 0;
		Dir = 1;
	}
	else if(localport == 2)
	{
		Dir = 0xFF;
	}
	else
	{
		Dir = 7;
	}

	config = (BYTE*)malloc(sizeof(BYTE)*3);

	config[0] = localport;
	config[1] = enable;
	config[2] = Dir;

	if(dscDIOSetConfig(dscb,config)!= DE_NONE)
	{
		errorCheck ErrorCheck();
		return ;
	}

	if(localport == 3)
		cout<< "Enter Bit (0-2):or q to quit :";
	else
		cout<< "Enter Bit (0-7):or q to quit :";

	if ( (dscDIOOutputBit(dscb,localport,localBitNumber,localBitValue) != DE_NONE) )
	{
		errorCheck ErrorCheck();
		return;
	}
}
//=============================================================================
// Name: enable()
// Desc: Program a port A-D by sending a digital value to the selected
// 	  port's bit register.
// Parameters:void
// Return: void
//=============================================================================
void byte::enable(uint8_t localport,uint8_t localBitNumber)
{
	BYTE* config = NULL;
	int enable = 0;
	int Dir = 1;
	

	if(localport==0)
	{
		enable = 0;
		Dir = 1;
	}

	config = (BYTE*)malloc(sizeof(BYTE)*3);

	config[0] = localport;
	config[1] = enable;
	config[2] = Dir;

	if(localBitNumber == 0)
	{
		cout << "X enabled: \n";
	}
	else
	{
		cout << "Y enabled: \n";
	}

	if(dscDIOSetConfig(dscb,config)!= DE_NONE)
	{
		errorCheck ErrorCheck();
		return ;
	}
}
//=============================================================================
// Name: disable()
// Desc: Program a port A-D by sending a digital value to the selected
// 	  port's bit register.
// Parameters:void
// Return: void
//=============================================================================
void byte::disable(uint8_t localport,uint8_t localBitNumber)
{
	BYTE* config = NULL;
	int enable = 1;
	int Dir = 1;
	

	if(localport==0)
	{
		enable = 1;
		Dir = 1;
	}

	config = (BYTE*)malloc(sizeof(BYTE)*3);

	config[0] = localport;
	config[1] = enable;
	config[2] = Dir;

	if(localBitNumber == 0)
	{
		cout << "X disabled: \n";
	}
	else
	{
		cout << "Y disabled: \n";
	}
	
	if(dscDIOSetConfig(dscb,config)!= DE_NONE)
	{
		errorCheck ErrorCheck();
		return ;
	}
}
//=============================================================================
// Name: DIOPortLoopbackTest()
// Desc: loop back test on various ports
// Parameters: void
// Return: void
//=============================================================================
void byte::DIOPortLoopbackTest()
{
	BYTE* config = NULL;
	int output_port = 0,input_port = 0;
	BYTE output_byte = 0,input_byte = 0;
	int errorcount=0;
	int intBuff = 0;
	BYTE enable=0;
	int Dir=0;

	do
	{
		enable = 0;

		printf ("Enter port number for input (0-3) or  Enter -1 to go to Main menu:");
		fgets ( input_buffer, 20, stdin );
		sscanf ( input_buffer, "%d", &input_port );
		if(input_port==-1) return;

		config = (BYTE*)malloc(sizeof(BYTE)*3);

		config[0] = (BYTE)input_port;
		config[1] = (BYTE)enable;
		config[2] = 0x0;

		if(dscDIOSetConfig(dscb,config)!= DE_NONE)
		{
			errorCheck ErrorCheck();
			return ;
		}

		printf ("Enter port number for output (0-3):");
		fgets ( input_buffer, 20, stdin );
		sscanf ( input_buffer, "%d", &output_port );
		if(output_port==-1) return;

		if(output_port == 0 || output_port == 1)
		{
			Dir = 1;
		}
		else if(output_port == 2)
		{
			Dir = 0xFF;
		}
		else
		{
			Dir = 7;
		}
		
        if(output_port == 0 || output_port == 1)
		{
		printf ("Do u want to enable/diable the port (0-1):0-Enable 1-Disable:");
		fgets ( input_buffer, 20, stdin );
		sscanf ( input_buffer, "%d", &enable );
		}
		
		config[0] = (BYTE)output_port;
		config[1] = (BYTE)enable;
		config[2] = Dir;

		if(dscDIOSetConfig(dscb,config)!= DE_NONE)
		{
			errorCheck ErrorCheck();
			return ;
		}
			
		if (( input_port > DIOPORT_MAX || input_port < 0 ) || (output_port > DIOPORT_MAX || output_port < 0 ) )
		{
			printf ( "ERROR: Valid Port Numbers are: (0-%d)\n ", DIOPORT_MAX - 1);
			return;
		}

		errorcount=0;
		for(intBuff=0; intBuff<=255;intBuff++)
		{  
		  output_byte=(BYTE) intBuff;

		  if(output_port == 3 && output_byte > 8) break;
			
			if( (dscDIOOutputByte( dscb, output_port, output_byte ) != DE_NONE) )
			{
				errorCheck ErrorCheck();
				return;
			}
			
			if( (dscDIOInputByte ( dscb, input_port, &input_byte ) != DE_NONE) )
			{
				errorCheck ErrorCheck();
				return;
			}

			 
			if(output_byte !=input_byte)
			{
				  printf("Error: Output: 0x%x  Input: 0x%x \n",output_byte,input_byte);
					  errorcount+=1;
			}
		}
		printf("\nValues written : %d and Errors: %d \n",intBuff,errorcount);
	}while(1);
return;
}

//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//	     I. Driver Initialization
//	    II. Board Initialization
//	   III. DIO INPUT AND OUTPUT
//	    IV. Cleanup
//
//=============================================================================

int main ( void )
{

	int intBuff = 0; // temp variables of size int
	int temp = 0;   // temporary storage
   	char input_buffer[20];

	byte byteObject{};

   	memset ( &dsccbp, 0, sizeof(DSCCBP) );
	memset (portConfig,0, sizeof(int)*DIOPORT_MAX);

  
	//=========================================================================
	// I. DRIVER INITIALIZATION
	//
	//    Initializes the DSCUD library.
	//
	//    STEPS TO FOLLOW:
	//
	//	  1. initialize the driver, using the driver version for validation
	//=========================================================================

	if ( (dscInit ( DSC_VERSION ) != DE_NONE) )
	{
		errorCheck ErrorCheck();
		return 0;
	}
		
	//=========================================================================
	// II. BOARD INITIALIZATION
	//
	//	   Initialize the port_under_testboard. This function passes the various
	//	   hardware parameters to the driver and resets the hardware.
	//
	//     STEPS TO FOLLOW:
	//
	//	   1. set the board type to DSC_ZETA for the ZETA board
	//	   2. intialize and register the board with the driver, after which
	//		  the struct, dscb, now holds the handle for the board
	//=========================================================================

    cout<< "\nZeta DIO Function Application\n";
	 
	dsccb.boardtype = DSC_ZETA;
	
	cout<< "Enter the PC/104 base address (Default 0x200 hit ENTER) : ";

	fgets ( input_buffer, 20, stdin );
	if ( input_buffer[0] == '\n' )
	{
		dsccb.base_address = 0x200;
	}
	else
	{
	    sscanf ( input_buffer, "%hx", &dsccb.base_address );
	}

	printf ( "Enter the IRQ number (Default %d hit ENTER) : ",5 );
	fgets ( input_buffer, 20, stdin );
	if ( input_buffer[0] == '\n' )
	{
	    intBuff = 5;
	}
	else
	{
	    sscanf ( input_buffer, "%d", &intBuff );
	}
	dsccb.int_level = (BYTE)intBuff;
	

	if(dscInitBoard(DSC_ZETA, &dsccb, &dscb)!= DE_NONE)
	{
		errorCheck ErrorCheck();
		return 0;
	}

    //=========================================================================
	// III. DIO INPUT AND OUTPUT
	//
	//		Perform a set of byte-level inputs and outputs. We start by sending
	//		an output byte value of 0 to the selected digital I/O port and then
	//		read from that same port again to verify that the correct value was
	//		exchanged. For word and bit-level operations, the steps are nearly
	//		identical with a few minor changes to function names and the size
	//		of the data to be transferred.
	//
	//		NOTE: Remember that the bytes received from port are supposed to be
	//			  equal to the inversion of the bytes sent. That is, the input
	//			  bytes are equal to 255 minus the output bytes.
	//
	//		Guide:
	//
	//		1. Read a Byte from  port 
	//		2. Read a Byte from all ports
	//		3. Read all bits from a  port
	//		4. Write a Byte to port
	//		5. Write a Bit to a port
	//		6. Port loopback with 0-255 read/write repetitive\n
	//		q. Quit Program
	// 		Choose these options in any order from the menu!
	//=========================================================================

	cout << "\nEnter Valid Input String\n";
	do
	{
		byteObject.mParser.getInputString();
		parsingState ParsingState = byteObject.mParser.parsInput();
		
		uint8_t port = byteObject.mParser.getPort();
		uint8_t bit = byteObject.mParser.getBit();
		uint8_t bitValue = byteObject.mParser.getValue();

		switch(ParsingState)
		{
			case parsingState::SET:
				byteObject.writeBitDIOPort(port,bit,bitValue);
			break;

			case parsingState::READ:
				cout << "Bit Value: " << (byteObject.readBitsDIOPort(port,bit) & (1<<bit)) << endl;
			break;
			
			case parsingState::ENABLE:
				byteObject.enable(port,bit);
			break;

			case parsingState::DISABLE:
				byteObject.disable(port,bit);
			break;

			case parsingState::INVALID:
				cout << "Please Enter correct input format set/read[port x,bit x,bit_value x]" << endl;
			break;

			case parsingState::QUITE:
				input_buffer[0] = 'q';
			break;
		}

	} while ( input_buffer[0] != 'q' );

	//=========================================================================
	// IV. CLEANUP
	//
	//	   Cleanup any remnants left by the program and free the resources used
	//	   by the driver.
	//
	//     STEPS TO FOLLOW:
	//
	//	   1. free the driver resources
	//=========================================================================

	dscFree ( );

	printf ( "\nDSC Zeta DIOFunctions completed.\n" );

	return 0;

} // end main()
