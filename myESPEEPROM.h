#ifndef myESPEEPROM_H
#define myESPEEPROM_H

// the EEPROM utilities are trivial:

/* EEchksum(int addr)
 * 	in: int addr of EEPROM cell (base)
 *  out: sum of EEPROM cell and next (chksum) cell
 *  (s.b. zero)
 */
inline byte EEchksum(int addr) {
   return EEPROM.read(addr) + EEPROM.read(addr+1);
   }
/* getEEbyte(int addr)
 *  in: int addr of EEPROM cell
 *  out: byte at given address.
 */
inline byte getEEbyte(int addr) {
 return EEPROM.read(addr); 
 }
/* putEEbyte(int addr, byte datum)
 *  in: address and byte to store there
 *  out: nothing -- byte stored.
 */
inline void putEEbyte(int addr, byte datum) {
 EEPROM.write(addr, datum); EEPROM.commit(); 
 }
/* boolean updateEE(int addr, byte datum)
 *  in: address and datum
 *  out: truth of data written (updated)
 *       false if proffer data is same.
 */
inline boolean updateEE(int addr, byte datum) {
 if (EEPROM.read(addr) != datum) { 
	EEPROM.write(addr, datum); return true; 
	} return false; 
}
/* void sumChkEE(int addr, byte datum)
 *  in: address and datum
 *  out: nothing returned,
 * 		EEPROM updated with byte and checksum.
 */
inline void sumChkEE(int addr, byte datum) {
boolean flag;
 if(updateEE(addr, datum) & updateEE(addr+1, 0-datum))EEPROM.commit(); 
 }
/* uint8_t getEEDefault(uint8_t def, uint8_t addr)
 *  in: default value and address in EEPROM
 * 	out: value, either default or from EEPROM
 * 		default stored if no value found in EEPROM.
 */
uint8_t getEEDefault(uint8_t def, uint16_t addr) {
  if(EEchksum(addr) != 0) { // already stored?
    sumChkEE(addr, def);    // no, make it so
  }
  return (getEEbyte(addr)); // return in any case
}
#endif
