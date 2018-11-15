/*   
 *            Problem drawing BMP on OLED I2C SSD1306
 *            
 *                        "FLIP THE BYTES..."
 *  
 *  Copyright (c) 2018, Knottis
 *  All rights reserved.
 *  
 *  Prosjekt:  FLIPPING THE BMP-HEX DRAWING FOR THE "NEW" DRIVER ON SSD1306 OLED. 
 *  Name:      Flipping SSD1306 OLED HEX Data for Arduino - ATmega
 *  
 *  https://github.com/Knottis/Data-Flipping-SSD1306-OLED
 *   
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *     
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *      
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *      
 *    In addition, and without limitation, to the disclaimers of warranties 
 *    stated above and in the GNU General Public License version 3 (or any 
 *    later version), I offers this program subject to the following warranty 
 *    disclaimers and by using this program you acknowledge and agree to 
 *    the following:
 *    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
 *    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
 *    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
 *    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
 *    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
 *    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
 *    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
 *    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
 *    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
 *    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
 *    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
 *    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
 *    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
 *    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
 *    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
 *    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
 *    THE ABOVE. 
 *   
 *   
 *   Special thanks to  "Sams Teach Yorself Arduino Programming - in 24-Hours" - Richard Blum
 *   https://www.amazon.com/Arduino-Programming-Hours-Teach-Yourself/dp/0672337126
 *  
 *  (https://forum.arduino.cc/index.php?topic=434348.0)
 *     
 *  ============================
 *  DATA OUT ON THE:
 *  Serial Monitor Baud: 115.200
 *  ============================
 *  
 *  Tools:
 *  ------------------------------------------------------------------
 *  Online Convert BMP to HEX:
 *  http://javl.github.io/image2cpp/   =>>  128x64x8Pix_Horizontal.txt
 *  
 *  LCD Assistant:
 *  http://en.radzio.dxp.pl/bitmap_converter/
 *  ------------------------------------------------------------------
 *  
*/

// ================================================================================================
// INSERT YOUR HEX - BMP DATAFILE HERE.
// ================================================================================================

const char YOUR_BMP_LOGO[] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// ================================================================================================
// ================================================================================================




void setup() {
  // Use the Serial Monitor to view printed messages => 115.200 Baud.....(9600).
   Serial.begin(115200);
}

void loop() {
  UserMenu();
}

void UserMenu()
{
  Serial.println(F("\nWhich operation will you perform on your BMP-HEX Data?"));
  Serial.println(F("(1) - Start FLIP THE BYTES."));
  Serial.println(F("(2) - Start FLIP THE BYTES and INVERT the Black/White Colors."));
  while (!Serial.available());
    // Read data from serial monitor if received
    while (Serial.available()) 
    {
      char c = Serial.read();
      if (isAlphaNumeric(c)) 
      {
        if(c == '1') { 
          FlippingSSD1306OLED(false);
        }
        if(c == '2') {
          FlippingSSD1306OLED(true);             
        }
      }
    }
}

void FlippingSSD1306OLED(int InvertBlackWhite)
{
  Serial.println();
  Serial.println(F("########################################"));
  Serial.println(F("Starting up BMP-Flipping SSD1306-OLED..."));                  
  Serial.print(F("BMP Byte Sizes: "));
  Serial.println(sizeof(YOUR_BMP_LOGO));
  Serial.println(F("########################################"));
  if( InvertBlackWhite == true){
  Serial.println(F("  Your Picture Colors is INVERTED...")); 
  Serial.println(F("########################################"));
  }
  Serial.println();
  int i = 0, j = 0;
  byte ReversChar;
  char ReversBMP_LOGO[10] = {};
  Serial.print(F("PROGMEM = {"));
  Serial.println(); 
    for (i = 0 ; i < sizeof(YOUR_BMP_LOGO) ; i++)
    {
      ReversChar = YOUR_BMP_LOGO[i]; 
      // Flipping BIT 
      sprintf(ReversBMP_LOGO, "0x%02X", FlipingByte(ReversChar,InvertBlackWhite));
      Serial.print(ReversBMP_LOGO);
      ReversBMP_LOGO[0] = {};
      Serial.print(", ");
      if(j == 20){
        j=0;
        Serial.println();
      }
      else j++;
    }
  Serial.println();
  Serial.println(F("};"));
  Serial.println(F(""));
  Serial.println(F("########################################"));
  Serial.println(F("Copyright(©)-2018, Knottis")); 
  Serial.println(F("Finish..."));
  Serial.println(F("########################################"));  
}

byte FlipingByte(byte DataB, int InvertBlackWhite){
  char DataFlip = 0; 
  for(byte x = 0; x < 8; x++){
    DataFlip <<= 1;
    DataFlip |= DataB & 1;
    DataB >>= 1;
  }
  if( InvertBlackWhite == false) DataFlip = ~DataFlip;
  return DataFlip;
}
