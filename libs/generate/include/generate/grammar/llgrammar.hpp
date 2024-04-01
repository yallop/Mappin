#ifndef __MAPPIN_GEN_LLGRAMMAR__
#define __MAPPIN_GEN_LLGRAMMAR__

#include "../grammar.hpp"
#include <deque>
#include <utility>

namespace grammar {

class LLParseTable : public ParseTable {
public:
  LLParseTable(uint32_t, uint32_t, grammar_rules &, const char *);
  ~LLParseTable();

  ParseAction getAction(uint32_t, uint32_t) const override;

private:
  ParseAction *table;
  uint32_t rows;
  uint32_t cols;
};

class LLGrammar : public Grammar {
public:
  LLGrammar(const char *);
  ~LLGrammar();

  void finalize() override;
  void makeParseTable() override;
  void generateStackActions() override;
  void printParseTable() override;
  void printStackActions() override;

protected:
  LLParseTable *getParseTable() override;
  void getParse(inet::Node *) override;

private:
  void traverseRules(inet::Node *, std::deque<uint32_t> &);
  std::pair<std::deque<StackState>, std::deque<uint32_t>>
      findTerminal(uint32_t, uint32_t);
  LLParseTable *parse_table = nullptr;
};
} // namespace grammar
#endif
