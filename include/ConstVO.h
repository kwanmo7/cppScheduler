#ifndef CONST_VO_H
#define CONST_VO_H

#include <string>

namespace ConstVO{
  constexpr char suffixForTxt[] = "txt";  // txt 파일 접미사
  constexpr char suffixForCsv[] = "csv";  // csv 파일 접미사

  constexpr char textFileDelimiter = '|'; // txt 파일 구분자
  constexpr char csvFileDelimiter = ',';  // csv 파일 구분자
}

#endif // CONST_VO_H