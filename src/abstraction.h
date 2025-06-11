#include <boost/bimap.hpp>
#include "instructions.h"

const boost::bimap< pair<string, TokenType>, Byte>& construct_bimap();