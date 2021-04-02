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

void SimpleHeader::setSeqnum(unsigned int val) {
  packet.seq_Num = val;
}

unsigned int SimpleHeader::getSeqnum() const {
  return packet.seq_Num;
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

void SimpleHeader::setCRC2(unsigned int val) {
  packet.crc1_msb = (val>>16); // shift the integer to right by 16 bits to get the msb
  packet.crc1_lsb = (val&0x0000FFFF); // bitwise AND with 16 LSB bits set to 1.
}

unsigned int SimpleHeader::getCRC2() const {
  return packet.crc1_lsb | (packet.crc1_msb<<16);
}

string SimpleHeader::convertPacketToString() {
  string dataString = "";
  string payload(packet.data);

  dataString.append(to_string(getType()));
  dataString.append(to_string(getTR()));
  dataString.append(to_string(getWindow()));
  dataString.append(to_string(getSeqnum()));
  dataString.append(to_string(getHeader()));
  dataString.append(to_string(getTimestamp()));
  dataString.append(to_string(getCRC1()));
  dataString.append(payload);
  dataString.append(to_string(getCRC2()));

  return dataString;
}

void SimpleHeader::processString(string input) {
  unsigned int index = 0;

  string type = input.substr(index, 2);
  index += 2;
  setType(stoul(type, nullptr, 0));

  string tr = input.substr(index, 1);
  index += 1;
  setTR(stoul(tr, nullptr, 0));

  string window = input.substr(index, 5);
  index += 5;
  setWindow(stoul(window, nullptr, 0));

  string seqnum = input.substr(index, 8);
  index += 8;
  setSeqnum(stoul(seqnum, nullptr, 0));

  string length = input.substr(index, 16);
  index += 16;
  setHeader(stoul(length, nullptr, 0));

  string timestamp = input.substr(index, 32);
  index += 32;
  setTimestamp(stoul(timestamp, nullptr, 0));

  string crc1 = input.substr(index, 32);
  index += 32;
  setCRC1(stoul(crc1, nullptr, 0));

  string payload = input.substr(index, 4096);
  index += 4096;
  packet.data = payload;

  string crc2 = input.substr(index, 32);
  setCRC2(stoul(crc2, nullptr, 0));
}
