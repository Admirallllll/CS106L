#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
    auto space_its = ::find_all(source.begin(), source.end(), [](unsigned char c) {
        return std::isspace(c);
    });

    Corpus tokens;
    std::transform(
        space_its.begin(), space_its.end() - 1, 
        space_its.begin() + 1,
        std::inserter(tokens, tokens.begin()),
        [&source](auto it1, auto it2) { return Token(source, it1, it2); }
    );
    // use erase_if to remove empty tokens
    std::erase_if(tokens, [](const Token& token) { return token.content.empty(); });

    return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source,
                                 const Dictionary& dictionary) {
    namespace rv = std::ranges::views;
    auto view =
        source | rv::filter([&](const Token& token) {
            return !dictionary.contains(token.content);
        }) |
        rv::transform([&](const Token& token) {
            auto suggestions_view =
                dictionary | rv::filter([&](const std::string& dict_word) {
                    return levenshtein(token.content, dict_word) == 1;
                });

            std::set<std::string> suggestions{
                suggestions_view.begin(),
                suggestions_view.end()
            };

            return Misspelling{token, suggestions};
        })

        | rv::filter([](const Misspelling& misspelling) {
            return !misspelling.suggestions.empty();
        });

    return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"