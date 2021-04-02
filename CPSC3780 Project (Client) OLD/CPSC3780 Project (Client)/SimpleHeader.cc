#include "SimpleHeader.h"

SimpleHeader::SimpleHeader() {
  packet.length_msb = packet.length_lsb = 0;
}

void SimpleHeader::setHeader(unsigned int val) {
  packet.length_msb = (val>>8); // shift the integer to right by 8 bits to get the msb
  packet.length_lsb = (val&255); // bitwise AND with 8 LSB bits set to 1.
}

unsigned int SimpleHeader::getHeader() const {
  return packet.length_lsb | (packet.length_msb<<8);
}


void SimpleHeader::setType(unsigned int val) {
  packet.Type = val;
}

unsigned int SimpleHeader::getType() const {
  return packet.Type;
}

void SimpleHeader::setWindow(unsigned int val) {
  packet.Window = val;
}

unsigned int SimpleHeader::getWindow() const {
  return packet.Window;
}

void SimpleHeader::setTR(unsigned int val) {
  packet.TR = val;
}

unsigned int SimpleHeader::getTR() const {
  return packet.TR;
}

void SimpleHeader::setTimestamp(unsigned int val) {
  packet.Timestamp = val;
}

unsigned int SimpleHeader::getTimestamp() const {
  return packet.Timestamp;
}

void SimpleHeader::setCRC1(unsigned int val) {
  packet.crc1_msb = (val>>16); // shift the integer to right by 16 bits to get the msb
  packet.crc1_lsb = (val&0x0000FFFF); // bitwise AND with 16 LSB bits set to 1.
}

unsigned int SimpleHeader::getCRC1() const {
  return packet.crc1_lsb | (packet.crc1_msb<<16);
}

