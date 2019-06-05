/* An improved battery estimation function 
   This software, the ideas and concepts is Copyright (c) David Bird 2019 and beyond.
   All rights to this software are reserved.
   It is prohibited to redistribute or reproduce of any part or all of the software contents in any form other than the following:
   1. You may print or download to a local hard disk extracts for your personal and non-commercial use only.
   2. You may copy the content to individual third parties for their personal use, but only if you acknowledge
      the author David Bird as the source of the material.
   3. You may not, except with my express written permission, distribute or commercially exploit the content.
   4. You may not transmit it or store it in any other website or other form of electronic retrieval system for commercial purposes.
   5. You MUST include all of this copyright and permission notice ('as annotated') and this shall be included in all copies
      or substantial portions of the software and where the software use is visible to an end-user.
   THE SOFTWARE IS PROVIDED "AS IS" FOR PRIVATE USE ONLY, IT IS NOT FOR COMMERCIAL USE IN WHOLE OR PART OR CONCEPT.
   FOR PERSONAL USE IT IS SUPPLIED WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
   WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
   AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(readBattery());
  delay(1000);
}

String readBattery(){
  uint8_t percentage = 100;
  float voltage = analogRead(35) / 4096.0 * 7.23;      // LOLIN D32 (no voltage divider need already fitted to board.or NODEMCU ESP32 with 100K+100K voltage divider
  //float voltage = analogRead(39) / 4096.0 * 7.23;    // NODEMCU ESP32 with 100K+100K voltage divider added
  //float voltage = analogRead(A0) / 4096.0 * 4.24;    // Wemos / Lolin D1 Mini 100K series resistor added
  //float voltage = analogRead(A0) / 4096.0 * 5.00;    // Ardunio UNO, no voltage divider required
  Serial.println("Voltage = " + String(voltage));      // The voltage here needs to be reasonably accurate for a full LiFePO4 battery ~ 3.4v
  percentage = 4984.6172*pow(voltage,3) - 48287.7528*pow(voltage,2) + 155490.3329 * voltage - 166375.8607;
  if (voltage > 3.4) percentage = 100;
  else if (voltage <= 3.00) percentage = 0;
  return String(percentage)+"%";
}
