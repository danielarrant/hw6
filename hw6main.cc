/*
 * File:   binFileIOExample.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 *
 *  Perform Binary File IO and display results
 */


#include "hw6.h"
#include <iomanip>
#include <sstream>
#define BOX_WIDTH 25
#define MATRIX_HEIGHT 3
#define MATRIX_WIDTH 5
#define MATRIX_NAME_STRING "Binary File Contents"
int main()
{

  string magicNumber;
  string version;
  string numRecords;
  std:: stringstream sstream;
  int numRecordsInt = 0;
  string stringLenArr [5];
  string stringBufferArr[5];
  ofstream binOutfile;
  ifstream binInfile;


  BinaryFileHeader *myHeader = new  BinaryFileHeader();
  BinaryFileRecord *myRecord1 = new BinaryFileRecord();
  BinaryFileRecord *myRecord2 = new BinaryFileRecord();
  BinaryFileRecord *myRecord3 = new BinaryFileRecord();
  BinaryFileRecord *myRecord4 = new BinaryFileRecord();
  // Read in the header
  //ut << "Reading record to file: binaryfile.bin" << endl;

  binInfile.open ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  // should check for errors here.  Keeping it simple...

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  numRecordsInt = (int) (myHeader->numRecords);
 
  if (aGreaterThanB(numRecordsInt, 0))
  {
      binInfile.read((char *) myRecord1, sizeof(BinaryFileRecord));

      sstream << "strlen: " << unsigned(myRecord1->strLength);
      stringLenArr[0] = sstream.str();
      sstream.str("");

      sstream << myRecord1->stringBuffer;
      stringBufferArr[0] = sstream.str();
      sstream.str("");
  }
  if ( numRecordsInt > 1)
  {
      binInfile.read((char *) myRecord2, sizeof(BinaryFileRecord));

      sstream << "strlen: " << unsigned(myRecord2->strLength);
      stringLenArr[1] = sstream.str();
      sstream.str("");

      sstream << myRecord2->stringBuffer;
      stringBufferArr[1] = sstream.str();
      sstream.str("");
  }
  if ( numRecordsInt > 2)
  {
      binInfile.read((char *) myRecord3, sizeof(BinaryFileRecord));

      sstream << "strlen: " << unsigned(myRecord3->strLength);
      stringLenArr[2] = sstream.str();
      sstream.str("");

      sstream << myRecord3->stringBuffer;
      stringBufferArr[2] = sstream.str();
      sstream.str("");
  }
  if ( numRecordsInt > 3)
  {
      binInfile.read((char *) myRecord4, sizeof(BinaryFileRecord));

      sstream << "strlen: " << unsigned(myRecord4->strLength);
      stringLenArr[3] = sstream.str();
      sstream.str("");

      sstream << myRecord4->stringBuffer;
      stringBufferArr[3] = sstream.str();
      sstream.str("");
  }

 
  
  // Done... clean up
  binInfile.close();
  //out << "Finished reading record to file: binaryfile.bin" << endl;
  //ut << endl;

  // Display Results
  //cout << "Displaying Results with no extra formatting" << endl;
  //out << endl;
  //out << "magic number: |" << myHeader->magicNumber << "|" << endl;
  //out << "verison number: |" << myHeader->versionNumber << "|" << endl;
  //ut << "number of records: |" << myHeader->numRecords << "|" << endl;
  //ut << endl;

  // Lets try better formatting
  // cout << "Displaying Results with extra formatting" << endl;
  // cout << endl;
  sstream <<  "Magic: 0x"   << std::hex << std::uppercase << myHeader->magicNumber << std::dec << std::nouppercase;
  magicNumber = sstream.str();
  sstream.str("");
  sstream << "version: " << unsigned(myHeader->versionNumber) << endl;
  version = sstream.str();
  sstream.str("");
  sstream << "Num Records: " << unsigned(myHeader->numRecords) << endl;
  numRecords = sstream.str();
 


  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"x" ,"a", "b", "c"};

  const char 		*columnTitles[MATRIX_WIDTH+1] = {"x", "a", "b", "c", "d", "e"};
  


  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, magicNumber.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());

  for (int i = 0; i < numRecordsInt; i ++)
  {
    setCDKMatrixCell(myMatrix, i+2, 1, stringLenArr[i].c_str());
     setCDKMatrixCell(myMatrix, i+2, 2, stringBufferArr[i].c_str());
    
  }

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  cin.ignore();


  // Cleanup screen
  endCDK();

  
  return 0;
}

