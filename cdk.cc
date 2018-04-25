/* Arin Chase Faggard acf150430 | cs3377.502 Perkins */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdint.h>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;


class BinaryFileRecord {
public:
  int myVal;
  int version;
  int numRecords;
  int len1;
  char str1[10];
  int len2;
  char str2[10];
  int len3;
  char str3[16];
};


int main()
{
  /* Binary I/O */
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  // binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
  binInfile.close();
  stringstream stream;
  stream << hex << myRecord->myVal;
  string magicNumber("magic: 0x" + stream.str());
  stream.str("");
  stream << myRecord->version;
  string version_str("version: " + stream.str());
  stream.str("");
  stream << myRecord->numRecords;
  string numRecords_str("NumRecords: " + stream.str());
  stream.str("");
  stream << myRecord->len1;
  string len1_str("Length: " + stream.str());
  stream.str("");
  stream << myRecord->str1;
  string str1_str(stream.str());
  stream.str("");
  stream << myRecord->len2;
  string len2_str("Length: " + stream.str());
  stream.str("");
  stream << myRecord->str2;
  string str2_str(stream.str());
  stream.str("");
  stream << myRecord->len3;
  string len3_str("Length: " + stream.str());
  stream.str("");
  stream << myRecord->str3;
  string str3_str(stream.str());


  WINDOW *window;
  CDKSCREEN *cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char *rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char *columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

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
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
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
  setCDKMatrixCell(myMatrix, 1, 1,magicNumber.c_str());
  setCDKMatrixCell(myMatrix, 1, 2,version_str.c_str());
  setCDKMatrixCell(myMatrix, 1, 3,numRecords_str.c_str());
  setCDKMatrixCell(myMatrix, 2, 1,len1_str.c_str());
  setCDKMatrixCell(myMatrix, 2, 2,str1_str.c_str());
  setCDKMatrixCell(myMatrix, 3, 1,len2_str.c_str());
  setCDKMatrixCell(myMatrix, 3, 2,str2_str.c_str());
  setCDKMatrixCell(myMatrix, 4, 1,len3_str.c_str());
  setCDKMatrixCell(myMatrix, 4, 2,str3_str.c_str());
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
