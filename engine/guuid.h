#pragma once
#include <random>
#include <sstream>
#include <string>
class GUUID
{
public:
  static std::string GenerateRandomUUID(int length)
  {
    std::stringstream StringStream;

    for (int i = 0; i < length; i++)
    {
      unsigned char RandomChar = GetRandomCharacter();
      std::stringstream HexStream;
      HexStream << std::hex << int(RandomChar);

      std::string Hex = HexStream.str();
      StringStream << (Hex.length() < 2 ? '0' + Hex : Hex);
    }

    return StringStream.str();
  }

private:
  static char GetRandomCharacter()
  {
    std::random_device RandomDevice;
    std::mt19937 Generator(RandomDevice());
    std::uniform_int_distribution<> Distribution(0, 255);

    return static_cast<unsigned char>(Distribution(Generator));
  }
};
