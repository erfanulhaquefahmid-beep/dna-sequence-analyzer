#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <string>

namespace Translation {

std::string transcribeTemplateDNA(const std::string& dnaTemplate);
std::string aminoAcidForCodon(const std::string& codon);
std::string translateRNA(const std::string& rna);
std::string translateDNA(const std::string& dnaTemplate);

} // namespace Translation

#endif
