#include "ezlogger.h"
// Make sure will not encounter link error, redefinition
void Foo()
{
  int bar = 123;
  P(_(bar));
}