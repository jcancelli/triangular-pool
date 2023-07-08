#include "font.hpp"

#include <stdexcept>
#include <string>
#include <vector>

namespace pool {

namespace graphics {

sf::Font g_FontLucindaSansRegular;

struct FontConfig {
  std::string name;
  std::string filePath;
  sf::Font& variable;
};

void loadFonts() {
  const std::vector<FontConfig> FONT_CONFIGS{{"Lucinda Sans Regular",
                                              "resources/fonts/lucinda_sans_regular.ttf",
                                              g_FontLucindaSansRegular}};
  for (auto const& font : FONT_CONFIGS) {
    if (!font.variable.loadFromFile(font.filePath)) {
      throw std::runtime_error(std::string("Error: Could not load font \"") + font.name +
                               "\" from path: \"" + font.filePath + "\"");
    }
  }
}

}  // namespace graphics

}  // namespace pool