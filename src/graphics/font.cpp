#include "font.hpp"

#include <stdexcept>
#include <string>
#include <vector>

sf::Font g_FontLucindaSansRegular;

struct FontConfig {
  std::string name;
  std::string filePath;
  sf::Font& variable;
};

static const std::vector<FontConfig> FONT_CONFIGS{
    {"Lucinda Sans Regular", "", g_FontLucindaSansRegular}  //
};

void loadFonts() {
  for (auto const& font : FONT_CONFIGS) {
    if (!font.variable.loadFromFile(font.filePath)) {
      throw std::runtime_error(std::string("Error: Could not find \"") + font.name +
                               "\" font at path: \"" + font.filePath + "\"");
    }
  }
}