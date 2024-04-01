#include <generate/grammar/llgrammar.hpp>
#include <generate/grammar/lrgrammar.hpp>
#include <generate/grammar_parser.hpp>
#include <iostream>
#include <parse/draw.hpp>
#include <parse/inet.hpp>
#include <parse/nodes.hpp>
#include <parse/parser.hpp>
#include <util/util.hpp>

int main() {
  std::unique_ptr<grammar::Grammar> g;
  try {
    GrammarParser<grammar::LR0Grammar> g_parser("examples/test2.grammar");
    g = g_parser.parseGrammar();
    g->printGrammar();
    g->makeParseTable();
    g->printParseTable();
    g->generateStackActions();
    g->printStackActions();
  } catch (MappinException *e) {
    const char *e_str = e->what();
    std::cerr << e_str << std::endl;
    delete[] e_str;
    delete e;
    return -1;
  }

  std::string parseString = "ZERO MUL ONE";
  std::cout << "\nParsing: " << parseString << std::endl;

  inet::init();
  std::vector<grammar::Token> tokens = g->stringToTokens(parseString);
  inet::Node *output = inet::createParserNetwork(g->getStackActions(), tokens);

  while (!inet::interactions.empty()) {
    // inet::drawNetwork(g, false);
    inet::interact();
  }
  inet::drawNetwork(g, false);

  std::cout << "Parsing results: " << std::endl;
  g->getParses(output);

  return 0;
};
